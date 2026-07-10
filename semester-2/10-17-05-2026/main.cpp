#include <algorithm>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <vector>

struct FlaviusResult
{
    std::vector<std::size_t> eliminatedOrder;
    std::size_t winner = 0;
};

FlaviusResult flaviusJosephusOrder(std::size_t warriorsQuantity, std::size_t killStep);
FlaviusResult flaviusJosephusMarkedArray(std::size_t warriorsQuantity, std::size_t killStep);
FlaviusResult flaviusJosephusIterator(std::size_t warriorsQuantity, std::size_t killStep);
FlaviusResult getDeadMenQueryWithMap(std::size_t warriorsQuantity, std::size_t killStep);
void visualizeFromResult(std::size_t n, const FlaviusResult& result, std::ostream& out);

int main()
{
    constexpr std::size_t n = 10;
    constexpr std::size_t k = 3;

    FlaviusResult result = flaviusJosephusMarkedArray(n, k);

    std::cout << "Elimination order: ";
    for (std::size_t eliminated : result.eliminatedOrder)
    {
        std::cout << eliminated << ' ';
    }
    std::cout << "\nWinner: " << result.winner << "\n\n";

    visualizeFromResult(n, result, std::cout);


    return 0;
}

//
FlaviusResult flaviusJosephusOrder(std::size_t warriorsQuantity, std::size_t killStep)
{
    if (warriorsQuantity == 0)
        throw std::invalid_argument("warriorsQuantity must be greater than 0");
    if (killStep == 0)
        throw std::invalid_argument("killStep must be greater than 0");

    std::deque<std::size_t> dq;
    for (std::size_t i = 1; i <= warriorsQuantity; ++i)
        dq.push_back(i);

    FlaviusResult result;

    while (dq.size() > 1)
    {
        for (std::size_t r = 1; r < killStep; ++r)
        {
            dq.push_back(dq.front());
            dq.pop_front();
        }
        result.eliminatedOrder.push_back(dq.front());
        dq.pop_front();
    }

    result.winner = dq.front();
    return result;
}

FlaviusResult flaviusJosephusMarkedArray(std::size_t warriorsQuantity, std::size_t killStep)
{
    if (warriorsQuantity == 0)
        throw std::invalid_argument("warriorsQuantity must be greater than 0");
    if (killStep == 0)
        throw std::invalid_argument("killStep must be greater than 0");

    std::vector<std::size_t> soldiers(warriorsQuantity);

    for (std::size_t i = 0; i < soldiers.size(); ++i)
    {
        soldiers[i] = i + 1;
    }

    std::size_t aliveCounter = soldiers.size();
    std::size_t stepsToNextDeadMan = killStep;
    FlaviusResult result;

    while (aliveCounter > 1)
    {
        for (std::size_t& soldier : soldiers)
        {
            if (soldier != 0)
            {
                if (stepsToNextDeadMan > 1)
                {
                    stepsToNextDeadMan--;
                }
                else
                {
                    result.eliminatedOrder.push_back(soldier);
                    soldier = 0;
                    aliveCounter--;
                    stepsToNextDeadMan = killStep;
                }
            }
        }
    }

    for (std::size_t soldier : soldiers)
    {
        if (soldier != 0)
        {
            result.winner = soldier;
            break;
        }
    }

    return result;
}

FlaviusResult flaviusJosephusIterator(std::size_t warriorsQuantity, std::size_t killStep)
{
    // TODO:
    // 1) Validate input.
    // 2) Build dynamic list [1..peopleCount].
    // 3) Keep index i and counter from 1 upward.
    // 4) If i reaches end, wrap to 0.
    // 5) On each counter % k == 0: store list[i], erase list[i], keep i.
    // 6) Otherwise increment i.
    // 7) When one element remains, set winner.
    std::vector<std::size_t> soldiers(warriorsQuantity);

    for (std::size_t i = 0; i < soldiers.size(); ++i)
    {
        soldiers[i] = i + 1;
    }

    std::size_t i{0};
    FlaviusResult result;

    while (soldiers.size() > 1)
    {
        i = (i + killStep - 1) % soldiers.size();
        result.eliminatedOrder.push_back(soldiers[i]);
        soldiers.erase(soldiers.begin() + i);
    }
    result.winner = soldiers.front();
    return result;
}

FlaviusResult getDeadMenQueryWithMap(std::size_t warriorsQuantity, std::size_t killStep)
{
    if (warriorsQuantity == 0)
        throw std::invalid_argument("warriorsQuantity must be greater than 0");
    if (killStep == 0)
        throw std::invalid_argument("killStep must be greater than 0");

    std::vector<bool> alive(warriorsQuantity, true);
    std::size_t aliveCounter = warriorsQuantity;
    std::size_t stepsToNextDeadMan = killStep;

    FlaviusResult result;

    std::size_t i = 0;
    while (aliveCounter > 1)
    {
        if (alive[i])
        {
            if (stepsToNextDeadMan > 1)
            {
                --stepsToNextDeadMan;
            }
            else
            {
                result.eliminatedOrder.push_back(i + 1);
                alive[i] = false;
                --aliveCounter;
                stepsToNextDeadMan = killStep;
            }
        }

        i = (i + 1) % warriorsQuantity;
    }

    for (std::size_t j = 0; j < warriorsQuantity; ++j)
    {
        if (alive[j])
        {
            result.winner = j + 1;
            break;
        }
    }

    return result;
}

void visualizeFromResult(std::size_t n, const FlaviusResult& result, std::ostream& out)
{
    std::vector<std::size_t> alive;
    alive.reserve(n);
    for (std::size_t i = 1; i <= n; ++i)
    {
        alive.push_back(i);
    }

    out << "Initial circle: ";
    for (std::size_t x : alive)
    {
        out << x << ' ';
    }
    out << "\n\n";

    std::size_t step = 1;
    for (std::size_t dead : result.eliminatedOrder)
    {
        auto it = std::ranges::find(alive, dead);
        if (it == alive.end())
        {
            out << "Error: " << dead << " is already missing\n";
            continue;
        }

        out << "Step " << step++ << ": eliminated " << dead << "\n";
        alive.erase(it);

        out << "Remaining: ";
        for (std::size_t x : alive)
        {
            out << x << ' ';
        }
        out << "\n\n";
    }

    out << "Winner: " << result.winner << "\n";
}
