#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_StepBtn_clicked();
    void on_StartStopBtn_clicked();

private:
    Ui::MainWindow *ui;
    Simulation *sim;
};

#endif // MAINWINDOW_H
