#include "Date.h"

Date::Date()
{
    day = 1;
    month = 1;
    year = 1970;
}

void Date::setDate(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

void Date::setDay(int d)
{
    day = d;
}

void Date::setMonth(int m)
{
    month = m;
}

void Date::setYear(int y)
{
    year = y;
}

int Date::getDay()
{
    return day;
}

int Date::getMonth()
{
    return month;
}

int Date::getYear()
{
    return year;
}

int Date::getAge()
{
    int year = getCurrentDate().getYear();
    int month = getCurrentDate().getMonth();
    int day = getCurrentDate().getDay();
    int age = year - this->year;
    if (month < this->month) {
        age--;
    }
    else if (month == this->month) {
        if (day < this->day) {
            age--;
        }
    }
    return age;
}

void Date::defaultInputDate()
{
    std::cout << "Enter date of birth: ";
    std::cout << "Enter day: ";
    cin >> day;
    std::cout << "Enter month: ";
    cin >> month;
    std::cout << "Enter year: ";
    cin >> year;
}
Date Date::getCurrentDate()
{
    time_t t = time(0);
    struct tm now;
    localtime_s(&now, &t);
    int day = now.tm_mday;
    int month = now.tm_mon + 1;
    int year = now.tm_year + 1900;
    return Date(day, month, year);
}
string Date::convert2String()
{
    string s = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    return s;
}
Date::Date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

ostream& operator<<(ostream& os, const Date& d)
{
    os << d.day << "/" << d.month << "/" << d.year;
    return os;
}

bool operator==(const Date& d1, const Date& d2)
{
    return (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year);
}

bool operator<(const Date& d1, const Date& d2)
{
    if (d1.year < d2.year) {
        return true;
    }
    else if (d1.year == d2.year) {
        if (d1.month < d2.month) {
            return true;
        }
        else if (d1.month == d2.month) {
            if (d1.day < d2.day) {
                return true;
            }
        }
    }
    return false;
}

bool operator>(const Date& d1, const Date& d2)
{
    if (d1 < d2 || d1 == d2) {
        return false;
    }
    return true;
}

bool operator<=(const Date& d1, const Date& d2)
{
    if (d1 < d2 || d1 == d2) {
        return true;
    }
    return false;
}

bool operator>=(const Date& d1, const Date& d2)
{
    if (d1 > d2 || d1 == d2) {
        return true;
    }
    return false;
}

bool operator!=(const Date& d1, const Date& d2)
{
    if (d1 == d2) {
        return false;
    }
    return true;
}

