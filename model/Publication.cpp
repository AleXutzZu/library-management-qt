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

std::ostream &operator<<(std::ostream &os, const Publication &publication) {
    return os << publication.toString();
}

std::string Publication::toString() const {
    std::string output;

    output += getType() + ",";
    output += title + ",";
    output += publicationDate.toString() + ",";
    output += join(authors, ";");

    return output;
}

std::string Publication::join(const std::vector<std::string> &vec, const std::string &sep) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) oss << sep;
        oss << vec[i];
    }
    return oss.str();
}