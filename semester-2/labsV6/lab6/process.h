#pragma once
#include <functional>


/**
 * @brief Processes the array: filters, transforms, builds result inside, returns it.
 *
 * @param src       Input array.
 * @param size      Size of input array.
 * @param filter    Filter predicate (lambda or callable).
 * @param transform Transform function (lambda or callable).
 * @param outSize   Output: number of elements written (passed by reference).
 * @return Pointer to new[]-allocated array of transformed values; nullptr if none. Caller must delete[].
 */
int* process(const int* src,
             int size,
             const std::function<bool(int)>& filter,
             const std::function<int(int)>& transform,
             int& outSize);

void printArr(const int* arr, int size);
