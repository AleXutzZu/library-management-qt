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

std::string Article::getType() const {
    return "Article";
}

std::string Article::toString() const {
    return Publication::toString() + "," + "NA" + "," + "NA" + "," + std::to_string(citations) + "," + journal;
}

QJsonObject Article::toJSON() const {
    auto baseObject = Publication::toJSON();
    baseObject["journal"] = QString::fromStdString(journal);
    baseObject["citations"] = citations;
    return baseObject;
}

std::shared_ptr<Article> ArticleUpdate::intoArticle(const Article &article) const {
    std::string newTitle = title.value_or(article.getTitle());
    std::vector<std::string> newAuthors = authors.value_or(article.getAuthors());
    Date newDate = publicationDate.value_or(article.getPublicationDate());
    int citationsCount = citations.value_or(article.getCitations());
    std::string newJournal = journal.value_or(article.getJournal());

    return std::make_shared<Article>(newAuthors, newTitle, newDate, newJournal, citationsCount);
}

