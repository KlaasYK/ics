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
  qDebug() << "performing a step";
  sim->doSimulationStep();
  ui->trafficview->setState(sim->getIntersections());
}

void MainWindow::on_StartStopBtn_clicked() {
  qDebug() << "Start Stop clicked";
  if (started) {
    timer->stop();
    started = false;
  } else {
    // every 500 ms
    timer->start(100);
    started = true;
  }
}
void MainWindow::on_StepBtn_clicked() {
  qDebug() << "Step clicked";
  if (!started) {
    step();
  }
}
