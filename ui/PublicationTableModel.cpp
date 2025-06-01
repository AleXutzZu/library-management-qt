//
// Created by AleXutzZu on 29/05/2025.
//

#include <QMessageBox>
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

    connect(&this->controller, &PublicationController::publicationUpdated, this,
            &PublicationTableModel::onPublicationUpdated);
}

void PublicationTableModel::onPublicationRemoved(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    endRemoveRows();
}

Qt::ItemFlags PublicationTableModel::flags(const QModelIndex &index) const {
    auto defaultFlags = QAbstractTableModel::flags(index);

    if (index.isValid()) {
        //Disable article fields for book rows and vice versa
        auto publication = controller.getPublications()[index.row()];
        if (publication->getType() == "Book") {
            if (index.column() == COL_JOURNAL || index.column() == COL_CITATIONS) return defaultFlags;
        }

        if (publication->getType() == "Article") {
            if (index.column() == COL_PAGES || index.column() == COL_PUBLISHER) return defaultFlags;
        }

        switch (index.column()) {
            case COL_TYPE:
            case COL_ACTIONS:
                return defaultFlags;
            default:
                return defaultFlags | Qt::ItemIsEditable;
        }
    }
    return defaultFlags;
}

bool PublicationTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    int row = index.row();
    auto publication = controller.getPublications()[row];

    if (publication->getType() == "Book") {
        BookUpdate payload;
        std::vector<std::string> authorsVec;
        bool result;
        switch (index.column()) {
            case COL_TITLE:
                payload.title = value.toString().trimmed().toStdString();
                if (payload.title.value().empty()) return false;
                break;
            case COL_AUTHORS:
                authorsVec = BasePublicationRepository::tokenize(value.toString().trimmed().toStdString(), ';');
                if (authorsVec.empty()) return false;
                payload.authors = authorsVec;
                break;
            case COL_DATE:
                try {
                    payload.publicationDate = Date(value.toString().trimmed().toStdString());
                } catch (std::invalid_argument &e) {
                    return false;
                }
                break;
            case COL_PUBLISHER:
                payload.publisher = value.toString().trimmed().toStdString();
                if (payload.publisher.value().empty()) return false;
                break;
            case COL_PAGES:
                payload.numberOfPages = value.toInt(&result);
                if (!result || payload.numberOfPages <= 0) {
                    return false;
                }
                break;
        }
        try {
            controller.updateBook(publication->getTitle(), std::move(payload));
        } catch (std::invalid_argument &e) {
            return false;
        }
        return true;
    } else {
        ArticleUpdate payload;
        std::vector<std::string> authorsVec;
        bool result;
        switch (index.column()) {
            case COL_TITLE:
                payload.title = value.toString().trimmed().toStdString();
                if (payload.title.value().empty()) {
                    return false;
                }
                break;
            case COL_AUTHORS:
                authorsVec = BasePublicationRepository::tokenize(value.toString().trimmed().toStdString(), ';');
                if (authorsVec.empty()) return false;
                payload.authors = authorsVec;
                break;
            case COL_DATE:
                try {
                    payload.publicationDate = Date(value.toString().trimmed().toStdString());
                } catch (std::invalid_argument &e) {
                    return false;
                }
                break;
            case COL_JOURNAL:
                payload.journal = value.toString().trimmed().toStdString();
                if (payload.journal.value().empty()) return false;
                break;
            case COL_CITATIONS:
                payload.citations = value.toInt(&result);
                if (!result || payload.citations <= 0) {
                    return false;
                }
                break;
        }
        try {
            controller.updateArticle(publication->getTitle(), std::move(payload));
        } catch (std::invalid_argument &e) {
            return false;
        }
        return true;
    }
}

void PublicationTableModel::onPublicationUpdated(int row) {
    auto tl = index(row, 0);
    auto br = index(row, COL_COUNT - 1);
    emit dataChanged(tl, br, {Qt::DisplayRole, Qt::EditRole});
}
