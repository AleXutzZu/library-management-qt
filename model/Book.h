//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_BOOK_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_BOOK_H

#include "Publication.h"

class Book : public Publication {
private:
    int numberOfPages;
    std::string publisher;
public:
    Book(const std::vector<std::string> &authors, const std::string &title, const Date &publicationDate,
         int numberOfPages, std::string publisher);

    [[nodiscard]] int getNumberOfPages() const;

    [[nodiscard]] const std::string &getPublisher() const;

    std::string getType() const override;
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_BOOK_H
