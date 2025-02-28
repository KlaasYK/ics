#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    sim = new Simulation();
    ui->trafficview->setState(sim->getIntersections());
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    delay = 100;
}

MainWindow::~MainWindow() {
    delete sim;
    delete ui;
    delete timer;
}

void MainWindow::updateUI()
{
    ui->trafficview->setState(sim->getIntersections());
    ui->CarsMoved->setText(QString::number(sim->getCarsMoved()));
    ui->WaitTime->setText(QString::number(sim->getWaitTime()));
    ui->Step->setText(QString::number(sim->getStepNumber()));
    ui->Cars->setText(QString::number(sim->getCarsTotal()));
}

void MainWindow::step() {
    int stepsize = ui->StepSizeEdit->value();
    for (int i = 0; i < stepsize; i++) {
        sim->doSimulationStep();
    }
    updateUI();
}

void MainWindow::on_ResetBtn_clicked() {
    sim->resetSimulation();
    updateUI();
}

void MainWindow::on_GreenSlider_valueChanged(int value) {
    sim->stepsGreen = value;
    ui->GreenNumber->setText(QString::number(value));
}

void MainWindow::on_StepDelay_valueChanged(int value) {
    delay = value;
    ui->DelayText->setText(QString::number(value));
}

void MainWindow::on_SimpleOption_clicked() {
    sim->algorithm = LightType::SIMPLE;
}

void MainWindow::on_TwoSidedOption_clicked() {
    sim->algorithm = LightType::TWOSIDED;
}

void MainWindow::on_TwoSidedLoop_clicked()
{
    sim->algorithm = LightType::TWOSIDEDLOOP;
}

void MainWindow::on_SimpleLoop_clicked() {
    sim->algorithm = LightType::SIMPLELOOP;
}

void MainWindow::on_SetCars_clicked()
{
    // Reset simulation, set number of cars
    sim->resetSimulation();
    sim->numCars = ui->NumCars->value();

    updateUI();
}

void MainWindow::stopTimer()
{
    timer->stop();
    ui->StartStopBtn->setText("Start");
    ui->StepBtn->setEnabled(true);
}

void MainWindow::on_StartStopBtn_clicked() {

    if (timer->isActive()) {
        qDebug() << "Stopped";
        stopTimer();
    } else {
        qDebug() << "Started";
        timer->start(delay);
        ui->StartStopBtn->setText("Stop");
        ui->StepBtn->setEnabled(false);
    }
}

void MainWindow::on_StepBtn_clicked() {
  step();
}

void MainWindow::on_SaveStatsBtn_clicked() {
    qDebug() << "SaveStatsBtn clicked";
    if (timer->isActive()) {
      stopTimer();
    }
    QString filename = QFileDialog::getSaveFileName(this, tr("Save stats"));
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "step numCars dequeuedCars minQueueTime maxQueueTime sumQueueTime" << endl;
        for (auto stat: sim->getStats()) {
            QString min = "?";
            QString max = "?";
            if (stat->validMin) {
                min = QString::number(stat->minQueueTime);
            }
            if (stat->validMax) {
                max = QString::number(stat->maxQueueTime);
            }
            stream << stat->time << "\t" << stat->numCars << "\t" << stat->dequeuedCars << "\t";
            stream << min << "\t" << max << "\t" << stat->sumQueueTime << endl;
        }
        // Closing ;)
        file.close();
    }
}
