_Pragma("once")

#include <chrono>

namespace base {

    class TimeTicks {
    public:
        using time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>;

        explicit TimeTicks() = default;
        
        explicit TimeTicks(const std::chrono::milliseconds& ticks) : ticks_(ticks) {}
        
        explicit TimeTicks(const time_point& point) : ticks_(point) {}

        bool is_null() const;

        // Returns the internal numeric value of the TimeTicks object (milliseconds)
        long long ToInternalValue() const {
            return ticks_.time_since_epoch().count();
        }

        // Now
        static TimeTicks Now();

        TimeTicks& operator=(const TimeTicks& other) {
            ticks_ = other.ticks_;
            return *this;
        }

        // Compute the difference between two times.
        std::chrono::milliseconds operator-(const TimeTicks& other) const {
            return (ticks_ - other.ticks_);
        }

        // Modify by some time delta.
        TimeTicks& operator+=(const std::chrono::milliseconds& delta) {
            ticks_ += delta;
            return *this;
        }

        TimeTicks& operator-=(const std::chrono::milliseconds& delta) {
            ticks_ -= delta;
            return *this;
        }

        // Return a new TimeTicks modified by some delta.
        TimeTicks operator+(const std::chrono::milliseconds& delta) const {
            return TimeTicks(ticks_ + delta);
        }

        TimeTicks operator-(const std::chrono::milliseconds& delta) const {
            return TimeTicks(ticks_ - delta);
        }

        // Return a new TimeTicks modified by some delta.
        TimeTicks operator+(long long delta) const {
            return TimeTicks(ticks_ + std::chrono::milliseconds(delta));
        }

        TimeTicks operator-(long long delta) const {
            return TimeTicks(ticks_ - std::chrono::milliseconds(delta) );
        }

        // Comparison operators
        bool operator==(const TimeTicks& other) const {
            return ticks_ == other.ticks_;
        }

        bool operator!=(const TimeTicks& other) const {
            return ticks_ != other.ticks_;
        }

        bool operator<(const TimeTicks& other) const {
            return ticks_ < other.ticks_;
        }

        bool operator<=(const TimeTicks& other) const {
            return ticks_ <= other.ticks_;
        }

        bool operator>(const TimeTicks& other) const {
            return ticks_ > other.ticks_;
        }

        bool operator>=(const TimeTicks& other) const {
            return ticks_ >= other.ticks_;
        }

        static std::chrono::milliseconds FromDays(int days);
        static std::chrono::milliseconds FromHours(int hours);
        static std::chrono::milliseconds FromMinutes(int minutes);
        static std::chrono::milliseconds FromSeconds(long long secs);
        static std::chrono::milliseconds FromMilliseconds(long long ms);
        static std::chrono::milliseconds FromMicroseconds(long long us);

    private:
        time_point ticks_;
    };

} // end base
