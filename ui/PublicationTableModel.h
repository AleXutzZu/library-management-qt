//
// Created by AleXutzZu on 29/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONTABLEMODEL_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONTABLEMODEL_H


#include <QAbstractTableModel>
#include "../model/Publication.h"
#include "../controller/PublicationController.h"

class PublicationTableModel : public QAbstractTableModel {
Q_OBJECT
private:
    const PublicationController &controller;

    enum Columns {
        COL_TYPE,
        COL_TITLE,
        COL_AUTHORS,
        COL_DATE,
        COL_PAGES,
        COL_PUBLISHER,
        COL_CITATIONS,
        COL_JOURNAL,
        COL_ACTIONS,
        COL_COUNT
    };

    static std::string join(const std::vector<std::string> &vec, const std::string &sep);

private slots:
    void onPublicationAdded(int row);



public:
    explicit PublicationTableModel(const PublicationController &controller,
                                   QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONTABLEMODEL_H
