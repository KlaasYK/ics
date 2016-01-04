#include "customopenglwidget.h"

#include <QPainter>

CustomOpenGLWidget::CustomOpenGLWidget(QWidget *Parent)
    : QOpenGLWidget(Parent) {
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

CustomOpenGLWidget::~CustomOpenGLWidget() {}

void CustomOpenGLWidget::setState(QVector<Intersection *> intersections,
                                  QVector<Car *> cars) {
  intersections = intersections;
  cars = cars;
  update();
}

void CustomOpenGLWidget::paintEvent(QPaintEvent *event) {
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing, true);
  // make sure the drawing area is square
  int side = qMin(width(), height());
  painter.scale(side / (380.0 * 3), side / (380.0 * 3));
  paintGrid(painter);
  painter.translate(240, 175);
  paintCar(painter);
  painter.end();
}

void CustomOpenGLWidget::paintGrid(QPainter &painter) {
  painter.save();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      paintIntersectionGrid(painter);
      painter.translate(380, 0);
    }
    painter.translate(-380 * 3, 380);
  }
  painter.restore();
}

void CustomOpenGLWidget::paintIntersectionGrid(QPainter &painter) {
  QLine corner[] = {QLine(160, 0, 160, 160), QLine(160, 160, 0, 160)};
  QLine lanes[] = {QLine(190, 0, 190, 160),   QLine(160, 160, 220, 160),
                   QLine(160, 40, 220, 40),   QLine(160, 80, 220, 80),
                   QLine(160, 120, 220, 120), QLine(160, 0, 220, 0)};
  painter.save();
  // make road
  painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
  painter.setPen(Qt::gray);
  painter.drawRect(160, 160, 60, 60);
  for (int i = 0; i < 4; i++) {
    painter.drawRect(160, 0, 60, 160);
    painter.translate(190, 190);
    painter.rotate(90);
    painter.translate(-190, -190);
  }
  painter.restore();
  painter.save();
  // draw lanes
  painter.setPen(QPen(Qt::white, 2, Qt::DashLine));
  for (int i = 0; i < 4; i++) {
    painter.drawLines(lanes, 6);
    painter.translate(190, 190);
    painter.rotate(90);
    painter.translate(-190, -190);
  }
  painter.restore();
  painter.save();
  // draw road boundaries and traffic signs
  painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
  for (int i = 0; i < 4; i++) {
    painter.setBrush(QBrush(Qt::white));
    painter.drawLines(corner, 2);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(150, 140, 10, 10);
    painter.translate(190, 190);
    painter.rotate(90);
    painter.translate(-190, -190);
  }
  painter.restore();
}

void CustomOpenGLWidget::paintCar(QPainter &painter) {
  painter.save();
  painter.setPen(Qt::gray);
  painter.setBrush(QBrush(QColor(0, 255, 255)));
  painter.drawRoundedRect(-15, -10, 30, 20, 4, 4);
  painter.setPen(QPen(QColor(0, 255, 255), 1, Qt::SolidLine));
  painter.setBrush(QBrush(QColor(0, 155, 255)));
  painter.drawRoundedRect(-7, -7, 18, 14, 4, 4);
  painter.restore();
}
