#pragma once

#include <string>

void printTestResult(const std::string& testName, bool result);

bool testTransform();
bool testCountIf();
bool testSort();

void runTests();