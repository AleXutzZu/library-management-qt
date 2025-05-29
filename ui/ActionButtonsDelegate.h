//
// Created by AleXutzZu on 29/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_ACTIONBUTTONSDELEGATE_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_ACTIONBUTTONSDELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

class ActionButtonsDelegate : public QStyledItemDelegate {
Q_OBJECT

public:
    explicit ActionButtonsDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

signals:

    void editClicked(const QModelIndex &index);

    void deleteClicked(const std::string &title);
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_ACTIONBUTTONSDELEGATE_H
