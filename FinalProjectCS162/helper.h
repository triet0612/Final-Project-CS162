#pragma once

#include <cstring>
#include <string>
#include <string.h>

using namespace std;

#include "SinglyLinkedList.h"

int getNumberOfDigits(long long x);
void adjustString(string& s);
bool checkLeapYear(const int year);
bool checkValidDate(const int day, const int month, const int year);
bool readInteger(int &result);
bool checkIntersection(pair<int, int> a, pair<int, int> b);
int getMinutes(const string& t);