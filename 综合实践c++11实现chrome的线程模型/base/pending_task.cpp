#include "./pending_task.h"

namespace base {

    PendingTask::PendingTask() : sequence_num_(0) {}

    PendingTask::PendingTask(const PendingTask& other) {
        task_ = other.task_;
        sequence_num_ = other.sequence_num_;
        delayed_run_time_ = other.delayed_run_time_;
    }

    PendingTask::PendingTask(PendingTask&& other) noexcept {
        sequence_num_ = other.sequence_num_;
        delayed_run_time_ = other.delayed_run_time_;
        task_ = std::move(other.task_);
    }

    PendingTask::PendingTask(const closure& task) : sequence_num_(0) {
        task_ = task;
    }

    PendingTask::PendingTask(closure&& task) noexcept : sequence_num_(0) {
        task_ = std::move(task);
    }

    PendingTask::PendingTask(const closure& task, const TimeTicks& delayed_run_time) : sequence_num_(0) {
        task_ = task;
        delayed_run_time_ = delayed_run_time;
    }

    PendingTask::PendingTask(closure&& task, const TimeTicks& delayed_run_time) noexcept {
        task_ = std::move(task);
        delayed_run_time_ = delayed_run_time;
    }

    PendingTask& PendingTask::operator=(const PendingTask& other) {
        task_ = other.task_;
        sequence_num_ = other.sequence_num_;
        delayed_run_time_ = other.delayed_run_time_;
        return *this;
    }

    PendingTask& PendingTask::operator=(PendingTask&& other) noexcept {
        sequence_num_ = other.sequence_num_;
        delayed_run_time_ = other.delayed_run_time_;
        task_ = std::move(other.task_);
        return *this;
    }

    bool PendingTask::Equals(const PendingTask& other) const {
        return (this->sequence_num_ == other.sequence_num_);
    }

    bool PendingTask::callable() {
        return static_cast<bool>(task_);
    }

    void PendingTask::Run() {
        if (callable()) {
            task_();
        }
    }

    bool PendingTask::operator<(const PendingTask& other) const {
        // Since the top of a priority queue is defined as the "greatest" element, we
        // need to invert the comparison here.  We want the smaller time to be at the
        // top of the heap.

        if (delayed_run_time_ < other.delayed_run_time_)
            return false;

        if (delayed_run_time_ > other.delayed_run_time_)
            return true;

        // If the times happen to match, then we use the sequence number to decide.
        // Compare the difference to support integer roll-over.
        return (sequence_num_ > other.sequence_num_);
    }

    // TaskQueue
    bool TaskQueue::empty() {
        return _val.empty();
    }
    
    void TaskQueue::emplace_back(const PendingTask& task) {
        task.sequence_num_ = ++(this->sequence_num_);
        _val.emplace_back(task);
    }

    PendingTask TaskQueue::pick_front() noexcept {
        PendingTask o((_val.front()));
        _val.pop_front();
        return (o);
    }

    const PendingTask& TaskQueue::front() {
        return _val.front();
    }

    void TaskQueue::swap(TaskQueue& val) {
        _val.swap(val._val);
    }

} // end base
