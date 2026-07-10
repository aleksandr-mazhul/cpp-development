#ifndef MAZHUL_CPP_DEVELOPMENT_COUNTER_H
#define MAZHUL_CPP_DEVELOPMENT_COUNTER_H


class Counter
{
public:
    Counter(int current, int min, int max, int step)
    {
        if (min > max)
        {
            throw invalid_argument("ERROR: The minimum cannot be greater than the maximum");
        }

        if (current < min || current > max)
        {
            throw invalid_argument("ERROR: The current value cannot exceed the range");
        }

        this->current = current;
        this->min = min;
        this->max = max;
        this->step = step;
    }

    Counter(const Counter& other)
        : current(other.current),
          min(other.min),
          max(other.max),
          step(other.step),
          initial(other.initial)
    {
    }

    Counter(Counter&& other) noexcept
        : current(other.current),
          min(other.min),
          max(other.max),
          step(other.step),
          initial(other.initial)
    {
    }

    Counter& operator=(const Counter& other)
    {
        if (this == &other)
            return *this;
        current = other.current;
        min = other.min;
        max = other.max;
        step = other.step;
        initial = other.initial;
        return *this;
    }

    Counter& operator=(Counter&& other) noexcept
    {
        if (this == &other)
            return *this;
        current = other.current;
        min = other.min;
        max = other.max;
        step = other.step;
        initial = other.initial;
        return *this;
    }

    void increment()
    {
        if (current + step < max)
        {
            current += step;
        }
    }

    void decrement()
    {
        if (current - step >= min)
        {
            current -= step;
        }
    }

    void reset()
    {
        if (current != initial)
        {
            current = initial;
        }
    }

    int getCurrent() const
    {
        return current;
    }

    void setInitial(int initial)
    {
        if (initial >= min && initial <= max)
        {
            this->initial = initial;
        }
    }

    void printSequence() const
    {
        for (int i = current; i <= max; i += step)
        {
            cout << i << ' ';
        }
        cout << endl;
    }

private:
    int current{0};
    int min{0};
    int max{100};
    int step{1};
    int initial = current;
};

#endif //MAZHUL_CPP_DEVELOPMENT_COUNTER_H
