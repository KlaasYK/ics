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

private:
  Ui::MainWindow *ui;
  Simulation *sim;
  QTimer *timer;
  bool started;
};

#endif // MAINWINDOW_H
