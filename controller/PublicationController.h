//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H

#include "../repository/BasePublicationRepository.h"
#include "../model/UndoAction.h"
#include <stack>

class PublicationController {
private:
    BasePublicationRepository &repository;
    std::stack<std::unique_ptr<UndoAction>> actionsStack;

public:
    explicit PublicationController(BasePublicationRepository &repository);

    void addBook(const std::string &title, const std::vector<std::string> &authors, const Date &date, int pages,
                 const std::string &publisher);

    void addArticle(const std::string &title, const std::vector<std::string> &authors, const Date &date, int citations,
                    const std::string &journal);

    void undo();
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H
