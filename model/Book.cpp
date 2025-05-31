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

std::string Book::getType() const {
    return "Book";
}

std::string Book::toString() const {
    return Publication::toString() + "," + std::to_string(numberOfPages) + "," + publisher + ",NA,NA";
}

std::shared_ptr<Book> BookUpdate::intoBook(const Book &book) const {
    std::string newTitle = title.value_or(book.getTitle());
    std::vector<std::string> newAuthors = authors.value_or(book.getAuthors());
    Date newDate = publicationDate.value_or(book.getPublicationDate());
    int pages = numberOfPages.value_or(book.getNumberOfPages());
    std::string newPublisher = publisher.value_or(book.getPublisher());

    return std::make_shared<Book>(newAuthors, newTitle, newDate, pages, newPublisher);
}