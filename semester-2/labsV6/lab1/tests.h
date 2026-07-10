#pragma once
#include <string>

bool equals(double a, double b, double eps = 1e-6);

void printTestResult(const std::string& testName, bool result);

bool testInitArrayRange();

bool testReverseFullArray();

bool testCyclicLeftShift();

bool testSelectionSort();
