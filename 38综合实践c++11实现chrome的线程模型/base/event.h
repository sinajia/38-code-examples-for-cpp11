_Pragma("once");

#ifdef _WIN32
#include <Windows.h>
#else

#endif

#include "./time.h"

namespace base {

#ifdef _WIN32
    class WaitableEvent {
    public:
        explicit WaitableEvent(bool manual_reset, bool initially_signaled);
        explicit WaitableEvent(HANDLE event_handle);

        WaitableEvent(const WaitableEvent&) = delete;
        WaitableEvent(WaitableEvent&&) = delete;
        void operator=(const WaitableEvent&) = delete;    
        
        ~WaitableEvent();

        HANDLE Release();
        HANDLE handle() const { return handle_; }

        // Put the event in the un-signaled state.
        void Reset();

        // Put the event in the signaled state.  Causing any thread blocked on Wait
        // to be woken up.
        void Signal();

        // Wait indefinitely for the event to be signaled.
        void Wait();

        bool TimedWait(const std::chrono::milliseconds& max_time);

    private:
        HANDLE handle_ = 0;
    };

#else

#endif



} // end base
