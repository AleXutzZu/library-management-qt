//
// Created by AleXutzZu on 21/05/2025.
//

#include "Publication.h"

#include <utility>

Publication::Publication(const std::vector<std::string> &authors, std::string title, const Date &publicationDate)
        : authors(authors), title(std::move(title)), publicationDate(publicationDate) {}

const std::vector<std::string> &Publication::getAuthors() const {
    return authors;
}

const std::string &Publication::getTitle() const {
    return title;
}

const Date &Publication::getPublicationDate() const {
    return publicationDate;
}
