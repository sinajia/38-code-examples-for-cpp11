_Pragma("once")

#include <functional>
#include <list>
#include "./time.h"

namespace base {

    class PendingTask {
    public:
        using closure = std::function<void(void)>;

        PendingTask();
        
        PendingTask(const PendingTask& other);

        PendingTask(PendingTask&& other) noexcept;

        PendingTask(const closure& task);
        
        PendingTask(closure&& task) noexcept;

        PendingTask(const closure& task, const TimeTicks& delayed_run_time);
        
        PendingTask(closure&& task, const TimeTicks& delayed_run_time) noexcept;

        PendingTask& operator=(const PendingTask& other);

        PendingTask& operator=(PendingTask&& other) noexcept;

        bool Equals(const PendingTask& other) const;

        inline bool callable();

        void Run();

        bool operator<(const PendingTask& other) const;

        TimeTicks delayed_run_time_;
        mutable unsigned int sequence_num_ = 0;

    private:
        std::function<void(void)> task_;
    };

    // Queue of PendingTask
    class TaskQueue {
    public:
        TaskQueue() : sequence_num_(0) {
            _val.clear();
        }
        ~TaskQueue() {
            _val.clear();
        }
        bool empty();
        void emplace_back(const PendingTask& task);
        PendingTask pick_front() noexcept ;
        const PendingTask& front();
        void swap(TaskQueue& val);

    private:
        std::list<PendingTask> _val;
        unsigned int sequence_num_ = 0;

    };


} // end base
