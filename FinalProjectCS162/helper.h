#pragma once

#include <cstring>
#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>

using namespace std;

#include "SinglyLinkedList.h"
#include "Date.h"

int getNumberOfDigits(long long x);

void adjustString(string& s);

bool checkLeapYear(const int year);

bool checkValidDate(const int day, const int month, const int year);

bool readInteger(int &result);

bool checkIntersection(pair<int, int> a, pair<int, int> b);

int getMinutes(const string& t);

void printDates(ofstream& foutput, const Date& date, const string& s);

string doubleToStr(double x, int precision);

int getRandomInteger(const int l, const int r);

string integerToString(const int x);