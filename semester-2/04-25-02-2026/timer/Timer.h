#pragma once

class Timer
{
public:
    Timer();
    explicit Timer(int seconds);

    void set(int seconds);

    void start();

private:
    int remainingSeconds{100};
    void tick();
    bool isExpired() const;
    int getRemaining() const;
};
