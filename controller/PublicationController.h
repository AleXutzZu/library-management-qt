//
// Created by AleXutzZu on 21/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H

#include "../repository/BasePublicationRepository.h"
#include "../model/UndoAction.h"
#include <stack>
#include <QObject>

class PublicationController : public QObject {
Q_OBJECT
private:
    BasePublicationRepository &repository;
    std::stack<std::unique_ptr<UndoAction>> actionsStack;

public:
    explicit PublicationController(BasePublicationRepository &repository);

    void addBook(const std::string &title, const std::vector<std::string> &authors, const Date &date, int pages,
                 const std::string &publisher);

    void addArticle(const std::string &title, const std::vector<std::string> &authors, const Date &date, int citations,
                    const std::string &journal);

    [[nodiscard]] const std::vector<std::shared_ptr<Publication>> &getPublications() const;

    void removeByTitle(const std::string &title);

    void undo();

private slots:
    void onRepositoryDataAdded(int position);
    void onRepositoryDataRemoved(int position);
signals:
    void publicationAdded(int);
    void publicationRemoved(int);
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONCONTROLLER_H
