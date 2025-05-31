#include <QApplication>
#include <QFile>
#include "controller/PublicationController.h"
#include "repository/CsvPublicationRepository.h"
#include "ui/UserInterface.h"

int main(int argc, char *argv[]) {
    CsvPublicationRepository repo;

    repo.load("../publications.csv");

    PublicationController controller(repo);

    QApplication app(argc, argv);

    auto *userInterface = new UserInterface(controller);

    userInterface->setMinimumSize({1000, 640});
    userInterface->show();

    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
    }

    QObject::connect(qApp, &QCoreApplication::aboutToQuit, [&repo]() {
        repo.save("../publications.csv");
    });

    return QApplication::exec();
}
