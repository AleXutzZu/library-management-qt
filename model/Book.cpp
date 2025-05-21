//
// Created by AleXutzZu on 21/05/2025.
//

#include "Book.h"

#include <utility>

Book::Book(const std::vector<std::string> &authors, const std::string &title, const Date &publicationDate,
           int numberOfPages, std::string publisher) : Publication(authors, title, publicationDate),
                                                       numberOfPages(numberOfPages), publisher(std::move(publisher)) {}

int Book::getNumberOfPages() const {
    return numberOfPages;
}

const std::string &Book::getPublisher() const {
    return publisher;
}
