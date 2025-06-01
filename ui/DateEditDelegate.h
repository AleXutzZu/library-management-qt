//
// Created by AleXutzZu on 01/06/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_DATEEDITDELEGATE_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_DATEEDITDELEGATE_H

#include <QStyledItemDelegate>
#include <QDateEdit>

class DateEditDelegate : public QStyledItemDelegate {
Q_OBJECT
public:
    explicit DateEditDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *
    createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_DATEEDITDELEGATE_H
