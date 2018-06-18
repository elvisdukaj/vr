#pragma once

#include <chrono>

template<typename Clock = std::chrono::steady_clock>
class Timer {
public:
    using TimePoint = typename Clock::time_point;

    Timer()
    {
        start();
    }

    void start() noexcept
    {
        m_lastTimepoint = now();
    }

    double elapsed() const noexcept
    {
        auto t = now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t - m_lastTimepoint);
        return elapsed.count() / 1000000.0;
    }

private:
    TimePoint now() const noexcept
    {
        return Clock::now();
    }

private:
    TimePoint m_lastTimepoint;
};
