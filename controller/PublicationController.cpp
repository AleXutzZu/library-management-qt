//
// Created by AleXutzZu on 21/05/2025.
//

#include "PublicationController.h"

PublicationController::PublicationController(BasePublicationRepository &repository) : repository(repository) {

    connect(&repository, &BasePublicationRepository::dataAdded,
            this, &PublicationController::publicationAdded);

    connect(&repository, &BasePublicationRepository::dataRemoved,
            this, &PublicationController::publicationRemoved);

    connect(&repository, &BasePublicationRepository::dataUpdated,
            this, &PublicationController::publicationUpdated);
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

void PublicationController::removeByTitle(const std::string &title) {
    try {
        auto publication = repository.findByTitle(title);
        repository.removeByTitle(title);
        auto action = std::make_unique<UndoRemove>(repository, publication);
        actionsStack.push(std::move(action));
    } catch (const std::invalid_argument &e) {
        //TODO implement logging later
        throw;
    }
}

void PublicationController::updateBook(const std::string &title, BookUpdate &&payload) {
    auto publication = repository.findByTitle(title);
    if (publication == nullptr) throw std::invalid_argument("Could not find publication to update: " + title);

    if (publication->getType() != "Book") throw std::invalid_argument("Type mismatch: Book vs Article");

    auto *data = dynamic_cast<Book *>(publication.get());

    auto newBook = payload.intoBook(*data);

    try {
        repository.update(title, newBook);

        auto action = std::make_unique<UndoUpdate>(repository, publication, newBook);
        actionsStack.push(std::move(action));
    } catch (std::invalid_argument &e) {
        //TODO implement logging later
        throw;
    }
}
