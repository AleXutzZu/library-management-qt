//
// Created by AleXutzZu on 27/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_UNDOACTION_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_UNDOACTION_H


#include "../repository/BasePublicationRepository.h"

class UndoAction {
protected:
    BasePublicationRepository &repository;
    std::shared_ptr<Publication> item;

public:
    virtual void executeUndo() = 0;

    UndoAction(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item);

    virtual ~UndoAction() = default;
};

class UndoAdd: public UndoAction {

public:
    UndoAdd(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item);

    void executeUndo() override;
};

class UndoRemove: public UndoAction{
public:
    UndoRemove(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item);

    void executeUndo() override;
};

class UndoUpdate: public UndoAction {
private:
    std::shared_ptr<Publication> oldItem;
public:
    UndoUpdate(BasePublicationRepository &repository, const std::shared_ptr<Publication> &item,
               const std::shared_ptr<Publication> &oldItem);

    void executeUndo() override;
};

#endif //OOP_PROJECT_LIBRARYMANAGEMENT_UNDOACTION_H
