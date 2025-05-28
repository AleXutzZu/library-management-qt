#include <QApplication>
#include "controller/PublicationController.h"
#include "repository/CsvPublicationRepository.h"
#include "ui/UserInterface.h"

int main(int argc, char *argv[]) {
    CsvPublicationRepository repo;
    PublicationController controller(repo);

    QApplication app(argc, argv);

    auto *userInterface = new UserInterface(controller);

    userInterface->setMinimumSize({800, 640});
    userInterface->show();

    return QApplication::exec();
}
