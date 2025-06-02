//
// Created by AleXutzZu on 02/06/2025.
//

#include "PublicationFilterProxyModel.h"

void PublicationFilterProxyModel::setTitleFilter(const QString &title) {
    titleFilter = title;
    invalidateFilter();
}

void PublicationFilterProxyModel::setTypeFilter(const QString &type) {
    typeFilter = type == "Select type..." ? "" : type;
    invalidateFilter();
}

void PublicationFilterProxyModel::setAuthorFilter(const QString &author) {
    authorFilter = author;
    invalidateFilter();
}

void PublicationFilterProxyModel::setLogicalOperator(PublicationFilterProxyModel::LogicalOperator op) {
    logicOp = op;
    invalidateFilter();
}

bool PublicationFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    auto model = sourceModel();

    QString titleData = model->index(sourceRow, PublicationTableModel::Columns::COL_TITLE,
                                     sourceParent).data().toString();
    QString typeData = model->index(sourceRow, PublicationTableModel::Columns::COL_TYPE,
                                    sourceParent).data().toString();
    QString authorsData = model->index(sourceRow, PublicationTableModel::Columns::COL_AUTHORS,
                                       sourceParent).data().toString();

    bool titleMatch = titleFilter.isEmpty() || titleData.contains(titleFilter, Qt::CaseInsensitive);
    bool typeMatch = typeFilter.isEmpty() || typeData.compare(typeFilter, Qt::CaseInsensitive) == 0;
    bool authorMatch = authorFilter.isEmpty() || authorsData.contains(authorFilter, Qt::CaseInsensitive);

    if (logicOp == And) return titleMatch && typeMatch && authorMatch;
    return (titleMatch && !titleFilter.isEmpty()) || (typeMatch && !typeFilter.isEmpty()) ||
           (authorMatch && !authorFilter.isEmpty());
}
