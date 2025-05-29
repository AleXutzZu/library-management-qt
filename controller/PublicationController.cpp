//
// Created by AleXutzZu on 21/05/2025.
//

#include "PublicationController.h"
#include "../model/Book.h"
#include "../model/Article.h"

PublicationController::PublicationController(BasePublicationRepository &repository) : repository(repository) {

    connect(&repository, &BasePublicationRepository::dataAdded,
            this, &PublicationController::onRepositoryDataAdded);

    connect(&repository, &BasePublicationRepository::dataRemoved,
            this, &PublicationController::onRepositoryDataRemoved);
}

void PublicationController::addBook(const std::string &title, const std::vector<std::string> &authors, const Date &date,
                                    int pages, const std::string &publisher) {

    try {
        auto publication = std::make_shared<Book>(authors, title, date, pages, publisher);
        repository.add(publication);

        auto action = std::make_unique<UndoAdd>(repository, publication);
        actionsStack.push(std::move(action));
    } catch (const std::invalid_argument &e) {
        //TODO implement logging later
        throw;
    }
}

void
PublicationController::addArticle(const std::string &title, const std::vector<std::string> &authors, const Date &date,
                                  int citations, const std::string &journal) {

    try {
        auto publication = std::make_shared<Article>(authors, title, date, journal, citations);
        repository.add(publication);

        auto action = std::make_unique<UndoAdd>(repository, publication);
        actionsStack.push(std::move(action));
    } catch (const std::invalid_argument &e) {
        //TODO implement logging later
        throw;
    }
}

void PublicationController::undo() {
    if (actionsStack.empty()) throw std::runtime_error("No actions to undo!");

    actionsStack.top()->executeUndo();
    actionsStack.pop();
}

const std::vector<std::shared_ptr<Publication>> &PublicationController::getPublications() const {
    return repository.getPublications();
}

void PublicationController::onRepositoryDataAdded(int position) {
    emit publicationAdded(position);
}

void PublicationController::onRepositoryDataRemoved(int position) {
    emit publicationRemoved(position);
}
