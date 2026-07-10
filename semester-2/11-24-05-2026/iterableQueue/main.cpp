#include <deque>
#include <iostream>
#include <string>

using namespace std;

struct Point
{
    int x;
    int y;
};

ostream& operator<<(ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

template <typename T>
class IterableQueue
{
public:
    using iterator = typename deque<T>::iterator;
    using constIterator = typename deque<T>::const_iterator;

    void push(const T& value)
    {
        data.push_back(value);
    }

    void pop()
    {
        data.pop_front();
    }

    T& front()
    {
        return data.front();
    }

    const T& front() const
    {
        return data.front();
    }

    T& back()
    {
        return data.back();
    }

    const T& back() const
    {
        return data.back();
    }

    bool empty() const
    {
        return data.empty();
    }

    size_t size() const
    {
        return data.size();
    }

    iterator begin()
    {
        return data.begin();
    }

    iterator end()
    {
        return data.end();
    }

    constIterator begin() const
    {
        return data.cbegin();
    }

    constIterator end() const
    {
        return data.cend();
    }

private:
    deque<T> data;
};

template <typename Container>
void printByIterator(const Container& c, const string& name)
{
    cout << name << ": ";

    for (auto it = c.begin(); it != c.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << '\n';
}

int main()
{
    IterableQueue<int> numbers;

    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    numbers.push(40);

    printByIterator(numbers, "queue (front -> back)");

    numbers.pop();

    printByIterator(numbers, "after pop");

    auto& first = numbers.front();
    first += 100;

    printByIterator(numbers, "after front modification");

    auto& last = numbers.back();
    last += 1000;

    printByIterator(numbers, "after back modification");

    cout << '\n';

    IterableQueue<Point> points;

    points.push(Point{1, 2});
    points.push(Point{10, 20});
    points.push(Point{100, 200});

    printByIterator(points, "points queue");

    cout << '\n';

    for (const auto& point : points)
    {
        cout << point.x << " " << point.y << '\n';
    }

    return 0;
}
