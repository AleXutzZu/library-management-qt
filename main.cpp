#include <QApplication>
#include <QFile>
#include "controller/PublicationController.h"
#include "repository/CsvPublicationRepository.h"
#include "ui/UserInterface.h"

int main(int argc, char *argv[]) {
    CsvPublicationRepository repo;
    PublicationController controller(repo);

    QApplication app(argc, argv);

    auto *userInterface = new UserInterface(controller);

    userInterface->setMinimumSize({1000, 640});
    userInterface->show();

    QFile file(":/style.qss"); // If using Qt resources, else just "style.qss"
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet); // Applies to entire application
    }

    return QApplication::exec();
}
