_Pragma("once")

#include <memory>
#include <mutex>
#include <queue>
#include <assert.h>
#include "./message_pump_default.h"
#include "./pending_task.h"

namespace base {

    class MessageLoop : public MessagePump::Delegate {
    public:
        enum Type {
            TYPE_DEFAULT = 0,
            TYPE_UI,
            TYPE_IO,
        };

        explicit MessageLoop(Type type = TYPE_DEFAULT);
        virtual ~MessageLoop();

        //static
        static MessageLoop* current();

        void PostTask(const PendingTask::closure& task);
        void PostDelayedTask(const PendingTask::closure& task, const std::chrono::milliseconds& delay);

        void Run();
        void Quit();
        Type type() const;

        bool is_running() const;
        //static
        static MessagePump* CreateMessagePumpForType(Type type);

        MessageLoop(const MessageLoop&) = delete;
        MessageLoop(MessageLoop&&) = delete;
        void operator=(const MessageLoop&) = delete;
        void operator=(MessageLoop&&) = delete;

    private:
        using DelayedTaskQueue = std::priority_queue<PendingTask>;

        void Init();
        void AddToDelayedWorkQueue(const PendingTask& pending_task);
        TimeTicks CalculateDelayedRuntime(const std::chrono::milliseconds& delay);
        void QuitInternal();
        void AppendTask(const PendingTask& task);
        bool RunPendingTask(PendingTask& pending_task);
        void ReloadWorkQueue();

        // MessagePump::Delegate methods:
        virtual bool DoWork() override;
        virtual bool DoDelayedWork(TimeTicks& next_delayed_work_time) override;
        virtual bool DoIdleWork() override;

        Type type_;
        bool running_;
        std::unique_ptr<MessagePump> pump_;
        TaskQueue incoming_queue_;
        TaskQueue working_queue_;
        DelayedTaskQueue delayed_work_queue_;
        std::mutex mutex_;
        TimeTicks recent_time_;
        thread_local static MessageLoop* thisptr_;
    
    };

} // end base
