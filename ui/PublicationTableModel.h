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
    PublicationController &controller;

private slots:

    void onPublicationAdded(int row);
    void onPublicationRemoved(int row);
    void onPublicationUpdated(int row);
public:
    explicit PublicationTableModel(PublicationController &controller,
                                   QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

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
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONTABLEMODEL_H
