//
// Created by AleXutzZu on 29/05/2025.
//

#include "PublicationTableModel.h"
#include "../model/Book.h"
#include "../model/Article.h"

int PublicationTableModel::rowCount(const QModelIndex &parent) const {
    return (int) controller.getPublications().size();
}

int PublicationTableModel::columnCount(const QModelIndex &parent) const {
    return COL_COUNT;
}

QVariant PublicationTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    const auto &publication = controller.getPublications()[index.row()];

    switch (index.column()) {
        case COL_TYPE:
            return QString::fromStdString(publication->getType());
        case COL_TITLE:
            return QString::fromStdString(publication->getTitle());
        case COL_AUTHORS:
            return QString::fromStdString(Publication::join(publication->getAuthors(), ", "));
        case COL_DATE:
            return QString::fromStdString(publication->getPublicationDate().toString());

    }

    if (auto *book = dynamic_cast<Book *>(publication.get())) {
        if (index.column() == COL_PAGES)
            return book->getNumberOfPages();
        else if (index.column() == COL_PUBLISHER)
            return QString::fromStdString(book->getPublisher());
    }

    if (auto *article = dynamic_cast<Article *>(publication.get())) {
        if (index.column() == COL_CITATIONS)
            return article->getCitations();
        else if (index.column() == COL_JOURNAL)
            return QString::fromStdString(article->getJournal());
    }

    return {};
}

QVariant PublicationTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        const QStringList headers = {
                "Type", "Title", "Authors", "Date",
                "Pages", "Publisher", "Citations", "Journal", "Actions"
        };
        return headers.value(section);
    }
    return {};
}

void PublicationTableModel::onPublicationAdded(int row) {
    beginInsertRows(QModelIndex(), row, row);
    endInsertRows();
}

PublicationTableModel::PublicationTableModel(PublicationController &controller,
                                             QObject *parent)
        : QAbstractTableModel(parent), controller(controller) {

    connect(&this->controller, &PublicationController::publicationAdded, this,
            &PublicationTableModel::onPublicationAdded);

    connect(&this->controller, &PublicationController::publicationRemoved, this,
            &PublicationTableModel::onPublicationRemoved);
}

void PublicationTableModel::onPublicationRemoved(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    endRemoveRows();
}
