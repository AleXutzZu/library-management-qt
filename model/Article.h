//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_ARTICLE_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_ARTICLE_H

#include "Publication.h"

class Article : public Publication {
private:
    std::string journal;
    int citations;

public:
    Article(const std::vector<std::string> &authors, const std::string &title, const Date &publicationDate,
            std::string journal, int citations);

    [[nodiscard]] const std::string &getJournal() const;

    [[nodiscard]] int getCitations() const;

    [[nodiscard]] std::string getType() const override;

    [[nodiscard]] std::string toString() const override;

    QJsonObject toJSON() const override;
};

struct ArticleUpdate : public PublicationUpdate {
    std::optional<std::string> journal;
    std::optional<int> citations;

    std::shared_ptr<Article> intoArticle(const Article &article) const;
};

#endif //OOP_PROJECT_LIBRARYMANAGEMENT_ARTICLE_H
