#include <iostream>

using namespace std;

enum class TrafficLight : std::uint8_t
{
    Red,
    Yellow,
    Green,
};

std::string trafficLightToString(TrafficLight light)
{
    switch (light)
    {
    case TrafficLight::Red:
        return "Red";
    case TrafficLight::Yellow:
        return "Yellow";
    case TrafficLight::Green:
        return "Green";
    }
}

std::string getTypeOfSequence(const int* array, std::size_t length)
{
    bool less{false}, more{false}, equals{false};

    for (std::size_t i = 0; i < length; ++i)
    {
        if (array[i] < array[i + 1])
        {
            less = true;
        }
        else if (array[i] > array[i + 1])
        {
            more = true;
        }
        else
        {
            equals = true;
        }
    }
    if (less && !equals && !more)
    {
        return "";
    }
}

int main()
{
    TrafficLight light{TrafficLight::Red};
    std::cout << trafficLightToString(light);
}
