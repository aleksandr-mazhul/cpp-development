#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

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
class IterableStack
{
public:
    // TODO(student): для LIFO-обхода замените на reverse_iterator / const_reverse_iterator.
    using iterator = typename vector<T>::reverse_iterator;
    using constIterator = typename vector<T>::const_reverse_iterator;

    // TODO(student): реализуйте стековые операции.
    void push(const T& value)
    {
        data.push_back(value);
    }

    void pop()
    {
        data.pop_back();
    }

    T& top()
    {
        return data[data.size() - 1];
    }

    const T& top() const
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
        return data.rbegin();
    }

    iterator end()
    {
        return data.rend();
    }

    constIterator begin() const
    {
        return data.crbegin();
    }

    constIterator end() const
    {
        return data.crend();
    }

private:
    vector<T> data;
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

template <typename T>
void printStack(stack<T> st, const string& name)
{
    cout << name << " (top -> bottom): ";
    while (!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << '\n';
}

template <typename T>
void printQueue(queue<T> q, const string& name)
{
    cout << name << " (front -> back): ";
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << '\n';
}

int main()
{
    vector<int> numbersVector = {1, 2, 3, 4, 5};
    deque<int> numbersDeque = {10, 20, 30, 40, 50};

    stack<int> numbersStack;
    numbersStack.push(100);
    numbersStack.push(200);
    numbersStack.push(300);

    queue<int> numbersQueue;
    numbersQueue.push(7);
    numbersQueue.push(8);
    numbersQueue.push(9);

    printByIterator(numbersVector, "vector");
    printByIterator(numbersDeque, "deque");
    // printByIterator(numbersStack, "stack");
    printQueue(numbersQueue, "queue");

    IterableStack<int> iterableStack;
    iterableStack.push(11);
    iterableStack.push(22);
    iterableStack.push(33);

    iterableStack.push(11);
    iterableStack.push(22);
    iterableStack.push(33);
    printByIterator(iterableStack, "iterable stack (top -> bottom)");


    iterableStack.pop();
    iterableStack.pop();
    iterableStack.pop();

    printByIterator(iterableStack, "iterable stack (top -> bottom)");

    auto& x = iterableStack.top();
    x++;
    printByIterator(iterableStack, "iterable stack (top -> bottom)");

    IterableStack<Point> points;
    points.push(Point{1, 2});
    points.push(Point{17, 5});
    points.push(Point{18, 2});
    points.push(Point{10, 9});
    printByIterator(points, "Points");

    Point& topPoint = points.top();
    topPoint.x = 100;
    topPoint.y = 200;
    printByIterator(points, "Points");

    for (auto el : points)
    {
        cout << el.x << " " << el.y << endl;
    }
    return 0;
}
