//
// Created by AleXutzZu on 21/05/2025.
//

#include <stdexcept>
#include "Date.h"

Date::Date(unsigned int year, unsigned int month, unsigned int day) : year(year), month(month), day(day) {
    bool res = checkValidDate(year, month, day);
    if (!res) throw std::invalid_argument("Date is invalid");
}

bool Date::checkValidDate(unsigned int year, unsigned int month, unsigned int day) {
    if (month < 1 || month > 12) return false;
    if (year < 1) return false;

    unsigned int maxDay = daysInMonth(month, year);
    if (day < 1 || day > maxDay) return false;

    return true;
}

unsigned int Date::getYear() const {
    return year;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getDay() const {
    return day;
}

Date::Date() : year(2000), day(1), month(1) {}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    return os << date.day << "/" << date.month << "/" << date.year;
}

std::istream &operator>>(std::istream &is, Date &date) {
    char separator;
    return is >> date.day >> separator >> date.month >> separator >> date.year;
}
