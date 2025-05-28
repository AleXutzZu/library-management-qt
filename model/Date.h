//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_DATE_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_DATE_H


#include <ostream>
#include <istream>

class Date {
private:
    unsigned int year, month, day;

    static bool isLeapYear(unsigned int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static unsigned int daysInMonth(unsigned m, unsigned int y) {
        switch (m) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return 31;
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                return isLeapYear(y) ? 29 : 28;
            default:
                return 0;
        }
    }

public:
    Date();

    Date(unsigned int year, unsigned int month, unsigned int day);

    [[nodiscard]] unsigned int getYear() const;

    [[nodiscard]] unsigned int getMonth() const;

    [[nodiscard]] unsigned int getDay() const;

    friend std::ostream &operator<<(std::ostream &os, const Date &date);

    friend std::istream &operator>>(std::istream &is, Date &date);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] std::string toString() const;
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_DATE_H
