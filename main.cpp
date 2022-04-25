#include <QApplication>
#include "tests.h"
#include "GUI.h"

int main(int argc, char *argv[]) {
    test();
    FileRepository<Locatar> repo("OwnFiles/repo.txt");
    Service service{repo};

    QApplication a(argc, argv);
    GUI gui(service);
    gui.show();

    return QApplication::exec();
}
