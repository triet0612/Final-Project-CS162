#pragma once
#include <time.h>
#include <iostream>

using namespace std;
class Date {
private:
    int day;
    int month;
    int year;
public:
    Date(int d, int m, int y);

    Date();

    void setDate(int d, int m, int y);

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    int getDay();
    int getMonth();
    int getYear();
    int getAge();

    void defaultInputDate();

    static Date getCurrentDate();

    friend ostream& operator<<(ostream& os, const Date& d);

    friend bool operator==(const Date& d1, const Date& d2);

    friend bool operator<(const Date& d1, const Date& d2);

    friend bool operator>(const Date& d1, const Date& d2);

    friend bool operator<=(const Date& d1, const Date& d2);

    friend bool operator>=(const Date& d1, const Date& d2) ;

    friend bool operator!=(const Date& d1, const Date& d2);

};

