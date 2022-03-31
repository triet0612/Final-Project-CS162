#pragma once
#include <time.h>
#include <iostream>
#include <string>

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

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getAge();

    static bool isLeapYear(int year) {
        if (year % 400 == 0) return true;
        if (year % 100 == 0) return false;
        if (year % 4 == 0) return true;
        return false;
    }

    static bool isValidDay(int day, int month, int year) {
        if (day < 1 || day > 31) return false;
        if (month == 2) {
            if (isLeapYear(year)) {
                if (day > 29) return false;
            }
            else {
                if (day > 28) return false;
            }
        }
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) return false;
        }
        return true;
    }

    void defaultInputDate();

    static Date getCurrentDate();
    
    string convert2String();

    friend ostream& operator<<(ostream& os, const Date& d);

    friend bool operator==(const Date& d1, const Date& d2);

    friend bool operator<(const Date& d1, const Date& d2);

    friend bool operator>(const Date& d1, const Date& d2);

    friend bool operator<=(const Date& d1, const Date& d2);

    friend bool operator>=(const Date& d1, const Date& d2) ;

    friend bool operator!=(const Date& d1, const Date& d2);

    Date& operator=(const string& s) {
        int day = 0;
        int month = 0;
        int year = 0;
        int i = 0;
        while (s[i] != '/') {
            day = day * 10 + (s[i] - '0');
            i++;
        }
        i++;
        while (s[i] != '/') {
            month = month * 10 + (s[i] - '0');
            i++;
        }
        i++;
        while (i < s.length()) {
            year = year * 10 + (s[i] - '0');
            i++;
        }
        this->day = day;
        this->month = month;
        this->year = year;
        return *this;
    };

};

