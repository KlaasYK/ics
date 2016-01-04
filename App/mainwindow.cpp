#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sim = new Simulation();
}

MainWindow::~MainWindow()
{
    delete sim;
    delete ui;
}

void MainWindow::on_StartStopBtn_clicked()
{
    qDebug() << "Start Stop clicked";
}
void MainWindow::on_StepBtn_clicked()
{
    qDebug() << "Step clicked";
    sim->doSimulationStep();
}


