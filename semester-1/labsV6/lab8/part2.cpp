#include <iostream>
using namespace std;

int main()
{
    int x[]{1, 3, 6, 2, 4, 7, 8, 78};
    const int N = sizeof(x) / sizeof(x[0]);

    int countSup = 0;
    int countInf = 0;

    for (int i = 0; i < N; ++i)
    {
        bool isMin = true;
        bool isMax = true;

        if (i > 0)
        {
            if (x[i - 1] < x[i]) isMin = false;
            if (x[i - 1] > x[i]) isMax = false;
        }

        if (i + 1 < N)
        {
            if (x[i + 1] < x[i]) isMin = false;
            if (x[i + 1] > x[i]) isMax = false;
        }

        if (isMin) ++countInf;
        if (isMax) ++countSup;
    }

    cout << "number of local minima: " << countInf << endl;
    cout << "number of local maxima: " << countSup << endl;
}
