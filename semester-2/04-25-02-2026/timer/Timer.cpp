#include "Timer.h"
#include <stdexcept>
#include <iostream>

Timer::Timer() : Timer(9)
{
}

Timer::Timer(int seconds) : remainingSeconds(seconds)
{
    if (seconds < 0)
        throw std::invalid_argument("Time cannot be negative");
}

void Timer::tick()
{
    if (remainingSeconds > 0)
        --remainingSeconds;
}

void Timer::set(int seconds)
{
    if (seconds < 0)
        throw std::invalid_argument("Time cannot be negative");

    remainingSeconds = seconds;
}

void Timer::start()
{
    while (!isExpired())
    {
        std::cout << "Remaining: "
            << getRemaining() << "\n";
        tick();
    }
}

bool Timer::isExpired() const
{
    return remainingSeconds == 0;
}

int Timer::getRemaining() const
{
    return remainingSeconds;
}
