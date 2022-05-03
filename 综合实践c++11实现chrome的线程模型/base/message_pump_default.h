_Pragma("once")

#include "./message_pump.h"
#include "./event.h"

namespace base {
    class MessagePumpDefault : public MessagePump {
        public:
            explicit MessagePumpDefault();
            virtual ~MessagePumpDefault();

            MessagePumpDefault(const MessagePumpDefault&) = delete;
            MessagePumpDefault(MessagePumpDefault&&) = delete;
            void operator=(const MessagePumpDefault&) = delete;
            void operator=(MessagePumpDefault&&) = delete;

            // MessagePump methods:
            virtual void Run(Delegate* delegate) final;
            virtual void Quit() final;
            virtual void ScheduleWork() final;
            virtual void ScheduleDelayedWork(const TimeTicks& delayed_work_time) final;

        private:
            // This flag is set to false when Run should return.
            bool keep_running_;

            // Used to sleep until there is more work to do.
            WaitableEvent event_;

            // The time at which we should call DoDelayedWork.
            TimeTicks delayed_work_time_;

    }; 

} // end base
