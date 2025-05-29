//
// Created by AleXutzZu on 29/05/2025.
//

#include "ActionButtonsDelegate.h"

void
ActionButtonsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);
}

bool ActionButtonsDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) {
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
