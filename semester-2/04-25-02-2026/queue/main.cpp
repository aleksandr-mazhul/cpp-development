#include <iostream>

template <typename T, size_t size>
class Queue
{
public:
    Queue()
        : head()
          , tail(-1)
          , queue()
    {
    }

    void add(T item);

private:
    size_t head = 0;
    T queue[size];
    size_t n;
    int tail;
};

template <typename T, size_t size>
void Queue<T, size>::add(T item)
{
    n++;
    if (n < size)
    {
        tail++;
    }
    else
    {
        tail++;
        tail %= size;
        head++;
        head %= size;
    }
    queue[tail] = item;
}

int main()
{
    Queue<int, 10> q;
    std::cout << "jjj";
    for (int i = 1; i <= 10; i++)
    {
        q.add(i);
    }
}


