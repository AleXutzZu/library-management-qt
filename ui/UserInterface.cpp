//
// Created by AleXutzZu on 27/05/2025.
//

#include <QMessageBox>
#include <QTableView>
#include "UserInterface.h"
#include "DateEditDelegate.h"
#include <QHeaderView>

UserInterface::UserInterface(PublicationController &controller) : controller(controller) {
    setUpUI();
    connectSignals();
}

void UserInterface::setUpUI() {
    this->setWindowTitle("Library Management");

    undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);

    // Create widgets
    titleEdit = new QLineEdit(this);
    authorsEdit = new QLineEdit(this);
    dateEdit = new QLineEdit(this);
    addButton = new QPushButton("Add", this);
    selectPublicationType = new QComboBox(this);

    selectPublicationType->addItem("Select type...");
    selectPublicationType->addItem("Book");
    selectPublicationType->addItem("Article");

    QModelIndex index = selectPublicationType->model()->index(0, 0);
    selectPublicationType->model()->setData(index, 0, Qt::UserRole - 1);

    titleEdit->setPlaceholderText("Enter title");
    authorsEdit->setPlaceholderText("Enter author names");
    dateEdit->setPlaceholderText("Enter date (dd/mm/yyyy)");

    //Book specific
    bookGroup = new QGroupBox("Book details", this);
    QFormLayout * bookFields = new QFormLayout(bookGroup);
    publisherEdit = new QLineEdit(this);
    numberOfPagesEdit = new QLineEdit(this);

    bookFields->addRow("Publisher", publisherEdit);
    bookFields->addRow("Page count", numberOfPagesEdit);

    publisherEdit->setPlaceholderText("Enter publisher");
    numberOfPagesEdit->setPlaceholderText("Enter number of pages");

    //Article specific
    articleGroup = new QGroupBox("Article details", this);
    QFormLayout * articleFields = new QFormLayout(articleGroup);
    citationsEdit = new QLineEdit(this);
    journalEdit = new QLineEdit(this);

    articleFields->addRow("Journal", journalEdit);
    articleFields->addRow("Citations", citationsEdit);

    citationsEdit->setPlaceholderText("Enter citation count");
    journalEdit->setPlaceholderText("Enter journal");

    // Create form layout
    QFormLayout * formLayout = new QFormLayout;
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Authors:", authorsEdit);
    formLayout->addRow("Date:", dateEdit);
    formLayout->addRow("Type: ", selectPublicationType);

    bookGroup->setVisible(false);
    articleGroup->setVisible(false);

    formLayout->addRow(bookGroup);
    formLayout->addRow(articleGroup);

    QVBoxLayout * formWithButtonLayout = new QVBoxLayout;

    formWithButtonLayout->addLayout(formLayout);

    QHBoxLayout * buttonsLayout = new QHBoxLayout;

    undoButton = new QPushButton("Undo", this);
    filterAndButton = new QRadioButton("Require all fields (filtering)", this);
    buttonsLayout->addWidget(addButton, 1);
    buttonsLayout->addWidget(filterAndButton, 1);
    buttonsLayout->addWidget(undoButton, 1);

    formWithButtonLayout->addLayout(buttonsLayout);

    //Table
    actionButtonsDelegate = new ActionButtonsDelegate(this);
    auto dateEditDelegate = new DateEditDelegate(this);

    table = new PublicationTableModel(controller, this);

    QTableView *tableView = new QTableView(this);

    proxy = new PublicationFilterProxyModel(this);

    proxy->setSourceModel(table);
    tableView->setModel(proxy);
    tableView->setItemDelegateForColumn(PublicationTableModel::Columns::COL_ACTIONS, actionButtonsDelegate);
    tableView->setItemDelegateForColumn(PublicationTableModel::Columns::COL_DATE, dateEditDelegate);


    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableView->horizontalHeader()->setSectionResizeMode(PublicationTableModel::Columns::COL_TYPE, QHeaderView::Fixed);
    tableView->setColumnWidth(PublicationTableModel::Columns::COL_TYPE, 50);

    tableView->horizontalHeader()->setSectionResizeMode(PublicationTableModel::Columns::COL_DATE, QHeaderView::Fixed);
    tableView->setColumnWidth(PublicationTableModel::Columns::COL_DATE, 80);

    tableView->horizontalHeader()->setSectionResizeMode(PublicationTableModel::Columns::COL_PAGES, QHeaderView::Fixed);
    tableView->setColumnWidth(PublicationTableModel::Columns::COL_PAGES, 40);

    tableView->horizontalHeader()->setSectionResizeMode(PublicationTableModel::Columns::COL_CITATIONS,
                                                        QHeaderView::Fixed);
    tableView->setColumnWidth(PublicationTableModel::Columns::COL_CITATIONS, 60);

    tableView->horizontalHeader()->setSectionResizeMode(PublicationTableModel::Columns::COL_ACTIONS,
                                                        QHeaderView::Fixed);
    tableView->setColumnWidth(PublicationTableModel::Columns::COL_ACTIONS, 60);

    // Main layout
    QVBoxLayout * mainLayout = new QVBoxLayout;

    QHBoxLayout * formRowLayout = new QHBoxLayout;

    formRowLayout->addLayout(formWithButtonLayout, 1);
    formRowLayout->addStretch(1);
    mainLayout->addLayout(formRowLayout);

    mainLayout->addWidget(tableView);
//    mainLayout->addStretch();

    setLayout(mainLayout);
}

void UserInterface::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, &UserInterface::onAddButtonClicked);
    connect(selectPublicationType, &QComboBox::currentIndexChanged, this, &UserInterface::onPublicationSelectorChanged);
    connect(undoButton, &QPushButton::clicked, this, &UserInterface::onUndoButtonClicked);
    connect(actionButtonsDelegate, &ActionButtonsDelegate::deleteClicked, this,
            &UserInterface::onDeleteActionButtonClicked);
    connect(undoShortcut, &QShortcut::activated, undoButton, &QPushButton::click);

    connect(titleEdit, &QLineEdit::textChanged, proxy, &PublicationFilterProxyModel::setTitleFilter);
    connect(selectPublicationType, &QComboBox::currentTextChanged, proxy, &PublicationFilterProxyModel::setTypeFilter);
    connect(authorsEdit, &QLineEdit::textChanged, proxy, &PublicationFilterProxyModel::setAuthorFilter);

    connect(filterAndButton, &QRadioButton::toggled, this, [this](bool checked) {
        proxy->setLogicalOperator(checked ? PublicationFilterProxyModel::And : PublicationFilterProxyModel::Or);
    });
}

void UserInterface::onAddButtonClicked() {
    QString title = titleEdit->text().trimmed();
    QStringList authors = authorsEdit->text().split(',', Qt::SkipEmptyParts);
    QString date = dateEdit->text().trimmed();

    if (selectPublicationType->currentIndex() == 0) {
        QMessageBox::warning(this, "Input Required", "Please select a publication type.");
        return;
    }

    // Validation
    if (title.isEmpty() || authors.isEmpty() || date.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "All fields must be filled.");
        return;
    }

    for (const QString &author: authors) {
        if (author.trimmed().isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Author names cannot be empty.");
            return;
        }
    }

    std::vector<std::string> authorsVec;
    for (const QString &author: authors) {
        authorsVec.push_back(author.trimmed().toStdString());
    }

    std::stringstream stream(date.toStdString());
    Date dateObj;
    if (!(stream >> dateObj)) {
        QMessageBox::warning(this, "Validation Error", "Date is not of valid format");
        return;
    }

    if (!dateObj.isValid()) {
        QMessageBox::warning(this, "Validation Error", "Date does not exist");
        return;
    }

    //Logic for adding book or article

    if (selectPublicationType->currentText() == "Book") {
        //Validating book specific fields

        QString publisher = publisherEdit->text().trimmed();
        QString numberOfPages = numberOfPagesEdit->text().trimmed();
        if (publisher.isEmpty() || numberOfPages.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "All fields must be filled");
            return;
        }
        bool result;
        int value = numberOfPages.toInt(&result);
        if (!result || value <= 0) {
            QMessageBox::warning(this, "Validation Error", "Number of pages should be positive");
            return;
        }

        try {
            controller.addBook(title.toStdString(), authorsVec, dateObj, value, publisher.toStdString());
            QMessageBox::information(this, "Success", "Book added successfully.");
            titleEdit->clear();
            authorsEdit->clear();
            dateEdit->clear();
            numberOfPagesEdit->clear();
            publisherEdit->clear();
        } catch (const std::invalid_argument &e) {
            QMessageBox::critical(this, "Error", "Publication with the same title already exists");
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    } else {
        QString journal = journalEdit->text().trimmed();
        QString citations = citationsEdit->text().trimmed();

        if (journal.isEmpty() || citations.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "All fields must be filled");
            return;
        }

        bool result;
        int value = citations.toInt(&result);
        if (!result || value <= 0) {
            QMessageBox::warning(this, "Validation Error", "Citation count should be positive");
            return;
        }

        try {
            controller.addArticle(title.toStdString(), authorsVec, dateObj, value, journal.toStdString());
            QMessageBox::information(this, "Success", "Article added successfully.");
            titleEdit->clear();
            authorsEdit->clear();
            dateEdit->clear();
            citationsEdit->clear();
            journalEdit->clear();
        } catch (const std::invalid_argument &e) {
            QMessageBox::critical(this, "Error", "Publication with the same title already exists");
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }
}

void UserInterface::onPublicationSelectorChanged(int index) {
    auto selected = selectPublicationType->itemText(index);

    if (selected == "Book") {
        bookGroup->setVisible(true);
        articleGroup->setVisible(false);
    } else {
        bookGroup->setVisible(false);
        articleGroup->setVisible(true);
    }
}

void UserInterface::onUndoButtonClicked() {
    try {
        controller.undo();
    } catch (const std::runtime_error &e) {
        QMessageBox::warning(this, "Error", "There is nothing left to undo!");
    }
}

void UserInterface::onDeleteActionButtonClicked(const std::string &title) {
    try {
        controller.removeByTitle(title);
    } catch (const std::invalid_argument &e) {
        QMessageBox::critical(this, "Error", "This publication does not exist");
    }
}
