//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATION_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATION_H

#include "../model/Publication.h"
#include <QAbstractTableModel>
#include <string>
#include <vector>
#include "Date.h"
#include <optional>

class Publication {
protected:
    std::vector<std::string> authors;
    std::string title;
    Date publicationDate;
public:

    static std::string join(const std::vector<std::string> &vec, const std::string &sep);

    Publication(const std::vector<std::string> &authors, std::string title, const Date &publicationDate);

    [[nodiscard]] const std::vector<std::string> &getAuthors() const;

    [[nodiscard]] const std::string &getTitle() const;

    [[nodiscard]] const Date &getPublicationDate() const;

    [[nodiscard]] virtual std::string getType() const = 0;

    [[nodiscard]] virtual std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const Publication &publication);
};

struct PublicationUpdate {
    std::optional<std::string> title;
    std::optional<std::vector<std::string>> authors;
    std::optional<Date> publicationDate;
};

#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATION_H
