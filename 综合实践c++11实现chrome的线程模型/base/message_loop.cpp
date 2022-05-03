#include "./message_loop.h"

namespace base {

    thread_local MessageLoop* MessageLoop::thisptr_ = nullptr;

    MessageLoop::MessageLoop(Type type) : type_(type), running_(false) {
        Init();
        pump_.reset(CreateMessagePumpForType(type));
    }

    MessageLoop::~MessageLoop() {
        thisptr_ = nullptr;
    }

    MessageLoop* MessageLoop::current() {
        return thisptr_;
    }

    void MessageLoop::PostTask(const PendingTask::closure& task) {
        PostDelayedTask(task, std::chrono::milliseconds::zero());
    }

    void MessageLoop::PostDelayedTask(const PendingTask::closure& task, const std::chrono::milliseconds& delay) {
        if (0 == delay.count()) {
            PendingTask t(task);
            AppendTask(t);
        }
        else {
            PendingTask t(task, CalculateDelayedRuntime(delay));
            AppendTask(t);
        }

        pump_->ScheduleWork();
    }

    void MessageLoop::Run() {
        running_ = true;
        pump_->Run(this);
        running_ = false;
    }

    void MessageLoop::Quit() {
        auto task = std::bind(&MessageLoop::QuitInternal, this);
        PostTask(task);
    }

    MessageLoop::Type MessageLoop::type() const { return type_; }

    bool MessageLoop::is_running() const {
        return running_;
    }

    //static
    MessagePump* MessageLoop::CreateMessagePumpForType(Type type) {
        if (MessageLoop::TYPE_DEFAULT == type) {
            return new MessagePumpDefault();
        }
        // todo
        return nullptr;
    }

    void MessageLoop::Init() {
        thisptr_ = this;
    }

    void MessageLoop::AddToDelayedWorkQueue(const PendingTask& pending_task) {
        delayed_work_queue_.emplace(pending_task);
    }

    TimeTicks MessageLoop::CalculateDelayedRuntime(const std::chrono::milliseconds& delay) {
        TimeTicks delayed_run_time = TimeTicks::Now() + delay;
        return delayed_run_time;
    }

    void MessageLoop::QuitInternal() {
        pump_->Quit();
    }

    void MessageLoop::AppendTask(const PendingTask& task) {
        std::lock_guard<std::mutex> guard(mutex_);
        incoming_queue_.emplace_back(task);
    }

    bool MessageLoop::RunPendingTask(PendingTask& pending_task) {
        pending_task.Run();
        return true;
    }

    void MessageLoop::ReloadWorkQueue() {
        if (!working_queue_.empty())
            return;

        std::lock_guard<std::mutex> guard(mutex_);
        if (!incoming_queue_.empty()) {
            incoming_queue_.swap(working_queue_);
        }
    }

    bool MessageLoop::DoWork() {
        for (;;) {
            ReloadWorkQueue();
            if (working_queue_.empty())
                break;

            //Execute oldest task.
            do {
                PendingTask pending_task = working_queue_.pick_front();
                if (!pending_task.delayed_run_time_.is_null()) {
                    AddToDelayedWorkQueue(pending_task);
                    // If we changed the topmost task, then it is time to reschedule.
                    if (delayed_work_queue_.top().Equals(pending_task))
                        pump_->ScheduleDelayedWork(pending_task.delayed_run_time_);
                }
                else {
                    if (RunPendingTask(pending_task))
                        return true;
                }
            } while (!working_queue_.empty());
        }
        //Nothing runned.
        return false;
    }
    
    bool MessageLoop::DoDelayedWork(TimeTicks& next_delayed_work_time) {
        if (delayed_work_queue_.empty()) {
            recent_time_ = next_delayed_work_time = TimeTicks();
            return false;
        }

        TimeTicks next_run_time = delayed_work_queue_.top().delayed_run_time_;
        if (next_run_time > recent_time_) {
            recent_time_ = TimeTicks::Now();
            if (next_run_time > recent_time_) {
                next_delayed_work_time = next_run_time;
                return false;
            }
        }

        PendingTask pending_task = delayed_work_queue_.top();
        delayed_work_queue_.pop();

        if (!delayed_work_queue_.empty()) {
            next_delayed_work_time = delayed_work_queue_.top().delayed_run_time_;
        }

        RunPendingTask(pending_task);
        return true;
    }
    
    bool MessageLoop::DoIdleWork() {
        return false;
    }


} // end base
