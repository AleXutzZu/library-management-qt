//
// Created by AleXutzZu on 27/05/2025.
//

#ifndef OOP_PROJECT_LIBRARYMANAGEMENT_USERINTERFACE_H
#define OOP_PROJECT_LIBRARYMANAGEMENT_USERINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>
#include "../controller/PublicationController.h"

class UserInterface : public QWidget {
Q_OBJECT
private:
    PublicationController &controller;

    //Publication generic fields
    QLineEdit *titleEdit;
    QLineEdit *authorsEdit;
    QLineEdit *dateEdit;

    //Book specific fields
    QGroupBox *bookGroup;
    QLineEdit *numberOfPagesEdit;
    QLineEdit *publisherEdit;

    //Article specific fields
    QGroupBox *articleGroup;
    QLineEdit *citationsEdit;
    QLineEdit *journalEdit;

    QComboBox *selectPublicationType;
    QPushButton *addButton;

    void setUpUI();

    void connectSignals();

public slots:

    void onAddButtonClicked();

    void onPublicationSelectorChanged(int index);

public:
    explicit UserInterface(PublicationController &controller);
};


#endif //OOP_PROJECT_LIBRARYMANAGEMENT_USERINTERFACE_H
