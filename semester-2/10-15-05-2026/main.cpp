#include <iostream>
#include <vector>


std::ostream& operator<<(std::ostream& os, const std::vector<int>& vector);

void fillVector(std::vector<int>& arr, int n);

int main()
{
    int n{10};
    int k{3};

    std::vector<int> people;
    fillVector(people, n);

    int index = 0;
    int step = 0;

    while (people.size() > 1)
    {
        int startIndex = index;
        bool firstPass = true;

        do
        {
            if (people.empty())
                break;

            step++;

            if (step == k)
            {
                std::cout << "Удаляем: " << people[index] << std::endl;
                people.erase(people.begin() + index);
                step = 0;

                if (people.empty())
                    break;

                if (index >= people.size())
                    index = 0;
            }
            else
            {
                index = (index + 1) % people.size();
            }

            firstPass = false;
        }
        while (index != startIndex || firstPass);

        std::cout << "После круга остались: " << people << std::endl;
    }

    std::cout << "Выжил: " << people[0] << std::endl;

    return 0;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vector)
{
    for (int i{0}; i < vector.size(); i++)
    {
        os << vector[i] << " ";
    }
    return os;
}

void fillVector(std::vector<int>& arr, int n)
{
    for (int i{1}; i <= n; i++)
    {
        arr.push_back(i);
    }
}
