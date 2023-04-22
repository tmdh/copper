#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Tareque Md Hanif");
    QCoreApplication::setApplicationName("Copper");
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow;
    window->show();
    app.exec();
    return 0;
}
