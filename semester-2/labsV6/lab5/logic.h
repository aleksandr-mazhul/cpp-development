#pragma once
/**
* @brief Determines whether a value should be processed further.
 *
 * @param value Input element value.
 * @return true  if the element passes the filter.
 * @return false if the element is skipped.
 */
bool filter(int value);


/**
 * @brief Transforms the input value.
 *
 * The function must be pure: it should not modify external state
 * and must return the transformed value.
 *
 * @param value Input element value.
 * @return Transformed value.
 */
int transform(int value);

/**
 * @brief Processes the array: filters, transforms, builds result inside, returns it.
 *
 * @param src       Input array.
 * @param size      Size of input array.
 * @param filter    Filter predicate.
 * @param transform Transform function.
 * @param outSize   Output: number of elements written (passed by reference).
 * @return Pointer to new[]-allocated array of transformed values; nullptr if none. Caller must
 * delete[].
 */
int* process(const int* src, int size,
             bool (*filter)(int),
             int (*transform)(int),
             int& outSize);

