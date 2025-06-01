//
// Created by AleXutzZu on 01/06/2025.
//

#include "DateEditDelegate.h"


QWidget *
DateEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto *editor = new QDateEdit(parent);
    editor->setDisplayFormat("dd/MM/yyyy");
    editor->setCalendarPopup(true);
    return editor;
}

void DateEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
    dateEdit->setDate(QDate::fromString(index.data().toString(), "dd/MM/yyyy"));
}


void DateEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
    model->setData(index, dateEdit->date().toString("dd/MM/yyyy"), Qt::EditRole);
}