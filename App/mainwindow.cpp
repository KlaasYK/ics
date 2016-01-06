#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  sim = new Simulation();
  ui->trafficview->setState(sim->getIntersections());
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(step()));
  started = false;
}

MainWindow::~MainWindow() {
  delete sim;
  delete ui;
  delete timer;
}

void MainWindow::step() {
  sim->doSimulationStep();
  ui->trafficview->setState(sim->getIntersections());
  ui->CarsMoved->setText(QString::number(sim->getCarsMoved()));
  ui->WaitTime->setText(QString::number(sim->getWaitTime()));
  ui->Step->setText(QString::number(sim->getStepNumber()));
  ui->Cars->setText(QString::number(sim->getCarsTotal()));
}

void MainWindow::on_ResetBtn_clicked() {
    sim->resetSimulation();
    ui->trafficview->setState(sim->getIntersections());
    ui->CarsMoved->setText(QString::number(sim->getCarsMoved()));
    ui->WaitTime->setText(QString::number(sim->getWaitTime()));
    ui->Step->setText(QString::number(sim->getStepNumber()));
    ui->Cars->setText(QString::number(sim->getCarsTotal()));
}

void MainWindow::on_GreenSlider_valueChanged(int value) {
    sim->stepsGreen = value;
    ui->GreenNumber->setText(QString::number(value));
}

void MainWindow::on_SimpleOption_clicked() {
    sim->algorithm = 0;
}

void MainWindow::on_TwoSidedOption_clicked() {
    sim->algorithm = 1;
}

void MainWindow::on_StartStopBtn_clicked() {
  qDebug() << "Start Stop clicked";
  if (started) {
    timer->stop();
    started = false;
    ui->StartStopBtn->setText("Start");
  } else {
    // every 500 ms
    timer->start(100);
    started = true;
    ui->StartStopBtn->setText("Stop");
  }
}
void MainWindow::on_StepBtn_clicked() {
  qDebug() << "Step clicked";
  if (!started) {
    step();
  }
}
