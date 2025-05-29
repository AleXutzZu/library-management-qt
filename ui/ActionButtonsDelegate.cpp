//
// Created by AleXutzZu on 29/05/2025.
//

#include "ActionButtonsDelegate.h"
#include "PublicationTableModel.h"
#include <QApplication>

void
ActionButtonsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionButton deleteButton;

    int width = option.rect.width();
    int height = option.rect.height();

    deleteButton.rect = QRect(option.rect.left(), option.rect.top(), width, height);
    deleteButton.text = "Delete";
    deleteButton.state = QStyle::State_Enabled;

    QApplication::style()->drawControl(QStyle::CE_PushButton, &deleteButton, painter);
}

bool ActionButtonsDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QModelIndex titleIndex = index.sibling(index.row(), PublicationTableModel::Columns::COL_TITLE);
        std::string title = model->data(titleIndex).toString().toStdString();
        emit deleteClicked(title);
    }

    return true;
}
