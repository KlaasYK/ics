#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    // TODO: read out screen width and height
    w.setGeometry(1920/2-400,1080/2-300,800,600);
    w.show();

    return a.exec();
}
