#include "./time.h"

namespace base {

    bool TimeTicks::is_null() const {
        return ( 0 == ticks_.time_since_epoch().count() );
    }

    // static
    TimeTicks TimeTicks::Now() {
        return TimeTicks(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()));
    }

    std::chrono::milliseconds TimeTicks::FromDays(int days) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<int, std::ratio<86400> >(days));
    }

    std::chrono::milliseconds TimeTicks::FromHours(int hours) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::hours(hours));
    }

    std::chrono::milliseconds TimeTicks::FromMinutes(int minutes) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::minutes(minutes));
    }

    std::chrono::milliseconds TimeTicks::FromSeconds(long long secs) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(secs));
    }

    std::chrono::milliseconds TimeTicks::FromMilliseconds(long long ms) {
        return std::chrono::milliseconds(ms);
    }
    
    std::chrono::milliseconds TimeTicks::FromMicroseconds(long long us) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::microseconds(us));
    }

} // end base
