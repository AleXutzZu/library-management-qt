//
// Created by AleXutzZu on 02/06/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONFILTERPROXYMODEL_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONFILTERPROXYMODEL_H


#include <QSortFilterProxyModel>
#include "PublicationTableModel.h"

class PublicationFilterProxyModel : public QSortFilterProxyModel {
Q_OBJECT
public:
    enum LogicalOperator {
        And, Or
    };
private:
    QString titleFilter;
    QString typeFilter;
    QString authorFilter;
    LogicalOperator logicOp = And;

public:
    void setTitleFilter(const QString &title);

    void setTypeFilter(const QString &type);

    void setAuthorFilter(const QString &author);

    void setLogicalOperator(LogicalOperator op);

    explicit PublicationFilterProxyModel(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_PUBLICATIONFILTERPROXYMODEL_H
