//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATION_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATION_H

#include <string>
#include <vector>
#include "Date.h"

class Publication {
protected:
    std::vector<std::string> authors;
    std::string title;
    Date publicationDate;

public:

    Publication(const std::vector<std::string> &authors, std::string title, const Date &publicationDate);

    [[nodiscard]] const std::vector<std::string> &getAuthors() const;

    [[nodiscard]] const std::string &getTitle() const;

    [[nodiscard]] const Date &getPublicationDate() const;

    [[nodiscard]] virtual std::string getType() const = 0;
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATION_H
