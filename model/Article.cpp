//
// Created by AleXutzZu on 21/05/2025.
//

#include "Article.h"

#include <utility>

Article::Article(const std::vector<std::string> &authors, const std::string &title, const Date &publicationDate,
                 std::string journal, int citations) : Publication(authors, title, publicationDate),
                                                       journal(std::move(journal)), citations(citations) {}

const std::string &Article::getJournal() const {
    return journal;
}

int Article::getCitations() const {
    return citations;
}
