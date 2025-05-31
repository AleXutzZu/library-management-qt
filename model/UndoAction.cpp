//
// Created by AleXutzZu on 27/05/2025.
//

#include "UndoAction.h"

UndoAction::UndoAction(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item) : repository(
        repository), item(item) {}

void UndoAdd::executeUndo() {
    repository.removeByTitle(item->getTitle());
}

UndoAdd::UndoAdd(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item) : UndoAction(
        repository, item) {}

void UndoRemove::executeUndo() {
    repository.add(item);
}

UndoRemove::UndoRemove(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item) : UndoAction(
        repository, item) {}

UndoUpdate::UndoUpdate(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item,
                       const std::shared_ptr<Publication> &oldItem) : UndoAction(repository, item), oldItem(oldItem) {}

void UndoUpdate::executeUndo() {
    repository.update(item->getTitle(), oldItem);
}
