//
// Created by AleXutzZu on 21/05/2025.
//

#include <stdexcept>
#include "Date.h"

Date::Date(unsigned int year, unsigned int month, unsigned int day) : year(year), month(month), day(day) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month: " + std::to_string(month));
    }

    if (year < 1) {
        throw std::invalid_argument("Invalid year: " + std::to_string(year));
    }

    unsigned int maxDay = daysInMonth(month, year);
    if (day < 1 || day > maxDay) {
        throw std::invalid_argument("Invalid day: " + std::to_string(day) +
                                    " for month " + std::to_string(month) +
                                    " in year " + std::to_string(year));
    }
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
