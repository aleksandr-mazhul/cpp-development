# include <iostream>
using namespace std;

bool isSimple(int number);

int sumOfSimpleNumbers(int* array, int n);

int main()
{
    int array[]{2, 4, 5, 7, 8, 10, 17, 19, 7, 20, 65, 324, 2, 53, 54, 6, 57, 68, 67, 89, 35, 2, 4, 7, 6, 12, 31, 31};
    int n = sizeof(array) / sizeof(array[0]);
    cout << sumOfSimpleNumbers(array, n);
}

bool isSimple(int number)
{
    if (number < 2) return false;
    for (int i{2}; i * i <= number; i++)
    {
        if (!(number % i))
        {
            return false;
        }
    }
    return true;
}

int sumOfSimpleNumbers(int* array, int n)
{
    int sum{0};
    int counter{0};
    for (int* p{array}; p < array + n; p++)
    {
        if (isSimple(*p) && !(counter % 3))
        {
            sum += *p;
        }
        counter++;
    }
    return sum;
}


