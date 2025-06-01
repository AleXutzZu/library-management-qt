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
    createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        auto *editor = new QDateEdit(parent);
        editor->setDisplayFormat("dd/MM/yyyy");
        editor->setCalendarPopup(true);
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        dateEdit->setDate(QDate::fromString(index.data().toString(), "dd/MM/yyyy"));
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        model->setData(index, dateEdit->date().toString("dd/MM/yyyy"), Qt::EditRole);
    }

};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_DATEEDITDELEGATE_H
