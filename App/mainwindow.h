#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "simulation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void step();
  void on_StepBtn_clicked();
  void on_StartStopBtn_clicked();
  void on_ResetBtn_clicked();
  void on_SimpleOption_clicked();
  void on_SimpleLoop_clicked();
  void on_TwoSidedOption_clicked();
  void on_TwoSidedLoop_clicked();
  void on_GreenSlider_valueChanged(int value);
  void on_StepDelay_valueChanged(int value);
  void on_SaveStatsBtn_clicked();
  void on_SetCars_clicked();

private:
  Ui::MainWindow *ui;
  Simulation *sim;
  QTimer *timer;
  int delay;
  void updateUI();
  void stopTimer();
};

#endif // MAINWINDOW_H
