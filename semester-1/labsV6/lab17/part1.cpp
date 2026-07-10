#include <iostream>
#include <cmath>
using namespace std;

void initArray(float*, float*);

void printArray(float*, float*);

float scalaProduct(float*, float*, float*);

const int N{100};

int main()
{
    srand(time(0));
    int n{0};
    float arrayA[N]{};
    float arrayB[N]{};


    cout << "enter the dimension of the array:" << endl;
    cin >> n;

    initArray(arrayA, arrayA + n);
    initArray(arrayB, arrayB + n);

    cout << "vector a" << endl;
    printArray(arrayA, arrayA + n);

    cout << "vector b" << endl;
    printArray(arrayB, arrayB + n);

    cout << "the scalar product of two vectors:" << endl;
    cout << scalaProduct(arrayA, arrayB, arrayA + n);

    return 0;
}

void initArray(float* begin, float* end)
{
    for (float* p{begin}; p < end; p++)
    {
        *p = rand() % 21;
    }
}

void printArray(float* begin, float* end)
{
    cout << "{";
    for (float* p{begin}; p < end; p++)
    {
        if (p != begin)
        {
            cout << ",";
        }
        cout << *p;
    }
    cout << "}" << endl;
}


float scalaProduct(float* beginA, float* beginB, float* end)
{
    float sum{0};
    float* pA{beginA};
    float* pB{beginB};

    while (pA < end)
    {
        sum += (*pA) * (*pB);
        pA++;
        pB++;
    }
    return sum;
}
