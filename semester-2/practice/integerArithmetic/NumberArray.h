#ifndef NUMBERARRAY_H
#define NUMBERARRAY_H

class NumberArray
{
private:
    int* array;
    int size;

    void inputArray();
    void printArray() const;

    int getMinDigit(int number) const;
    int getMaxDigit(int number) const;

    bool isSuitable(int number) const;

    int findAnswer() const;

public:
    NumberArray();
    ~NumberArray();

    void run();
};

#endif
