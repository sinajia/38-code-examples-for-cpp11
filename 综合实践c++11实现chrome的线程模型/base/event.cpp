#include "./event.h"
#include <assert.h>

namespace base {
#ifdef _WIN32

    WaitableEvent::WaitableEvent(bool manual_reset, bool signaled)
        : handle_(CreateEvent(NULL, manual_reset, signaled, NULL)) {
        // We're probably going to crash anyways if this is ever NULL, so we might as
        // well make our stack reports more informative by crashing here.
        assert(handle_);
    }

    WaitableEvent::WaitableEvent(HANDLE event_handle)
        : handle_(event_handle) {
        assert(handle_ != INVALID_HANDLE_VALUE);
    }

    HANDLE WaitableEvent::Release() {
        HANDLE rv = handle_;
        handle_ = NULL;
        return rv;
    }

    WaitableEvent::~WaitableEvent() {
        assert(handle_);
        CloseHandle(handle_);
        handle_ = NULL;
    }

    void WaitableEvent::Reset() {
        ResetEvent(handle_);
    }

    void WaitableEvent::Signal() {
        SetEvent(handle_);
    }

    // Wait indefinitely for the event to be signaled.
    void WaitableEvent::Wait() {
        DWORD result = WaitForSingleObject(handle_, INFINITE);
    }

    bool WaitableEvent::TimedWait(const std::chrono::milliseconds& max_time) {
        DWORD result = WaitForSingleObject(handle_, static_cast<DWORD>(max_time.count()));
        switch (result) {
        case WAIT_OBJECT_0:
            return true;
        case WAIT_TIMEOUT:
            return false;
        }
        // It is most unexpected that this should ever fail.  Help consumers learn
        // about it if it should ever fail.
        assert(0);
        return false;
    }

#else






#endif


} // end base
