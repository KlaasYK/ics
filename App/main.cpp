#include "mainwindow.h"
#include <QApplication>

#include <QScreen>
#include <QRect>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    // Center the window on screen
    QScreen *screen = a.primaryScreen();
    QRect size(screen->geometry());
    w.setGeometry(size.width()/2-(WIDTH/2),size.height()/2-(HEIGHT/2),WIDTH,HEIGHT);
    w.show();

    return a.exec();
}
