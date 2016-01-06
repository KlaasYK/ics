#include "customopenglwidget.h"

#include <QPainter>

#include <QDebug>

#define PBC

CustomOpenGLWidget::CustomOpenGLWidget(QWidget *Parent)
    : QOpenGLWidget(Parent) {
  painter = new QPainter();
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

CustomOpenGLWidget::~CustomOpenGLWidget() { delete painter; }

void CustomOpenGLWidget::setState(QVector<Intersection *> intersections) {
  this->intersections = intersections;
  update();
}

void CustomOpenGLWidget::paintEvent(QPaintEvent *event) {
  painter->begin(this);
  painter->setRenderHint(QPainter::Antialiasing, true);
  // make sure the drawing area is square
  int side = qMin(width(), height());
  painter->scale(side / (120.0 * 9), side / (120.0 * 9));
  paintGrid();
  paintCars();
  painter->end();
}

void CustomOpenGLWidget::paintGrid() {
  painter->save();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      paintIntersectionGrid(3 * i + j);
      painter->translate(360, 0);
    }
    painter->translate(-360 * 3, 360);
  }
  painter->restore();
}

void CustomOpenGLWidget::paintIntersectionGrid(int intersection) {
  QLine corner[] = {QLine(120, 0, 120, 120), QLine(120, 120, 0, 120)};
  QLine lanes[] = {QLine(150, 0, 150, 120), QLine(180, 0, 180, 120),
                   QLine(210, 0, 210, 120), QLine(120, 120, 240, 120)};
  painter->save();
  // make road
  painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));
  painter->setPen(Qt::gray);
  painter->drawRect(120, 0, 120, 360);
  painter->drawRect(0, 120, 360, 120);
  painter->restore();
  painter->save();
  // draw lanes
  painter->setPen(QPen(Qt::white, 2, Qt::SolidLine));
  for (int i = 0; i < 4; i++) {
    painter->drawLines(lanes, 4);
    painter->translate(180, 180);
    painter->rotate(90);
    painter->translate(-180, -180);
  }
  painter->restore();
  painter->save();
  // draw road boundaries and traffic signs
  painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
  for (int i = 0; i < 4; i++) {
    painter->setBrush(QBrush(Qt::white));
    painter->drawLines(corner, 2);
    painter->setBrush(QBrush(getLightColor(intersection, 2 * i+ 1)));
    painter->drawRect(110, 100, 10, 10);
    painter->setBrush(QBrush(getLightColor(intersection, 2 * i)));
    painter->drawRect(100, 100, 10, 10);
    painter->translate(180, 180);
    painter->rotate(90);
    painter->translate(-180, -180);
  }
  painter->restore();
}

QColor CustomOpenGLWidget::getLightColor(int intersection, int lane) {
  switch (intersections.at(intersection)->lights.at(lane)) {
  case Light::GREEN:
    return Qt::green;
  case Light::RED:
    return Qt::red;
  default:
    return Qt::cyan;
  }
}

void CustomOpenGLWidget::paintCars() {
  for (Intersection *inter : intersections) {
    for (Car *car : inter->getCars()) {
      painter->save();
      int x = 180;
      int y = 180;
      int pixx, pixy;
      // translate to the intersection
      x += 360 * (car->intersectionIndex % 3);
      y += 360 * (car->intersectionIndex / 3);
      pixx = x;
      pixy = y;
      painter->translate(x, y);
      // rotate to the lane
      int rot = 90 * (car->laneIndex / 2);
      painter->rotate(rot);
      // translate to lane position
      x = -45 + 30 * (car->laneIndex % 2);
      y = -75 + -30 * car->queuenumber;
#ifdef PBC
      // if the car falls outside the drawing and periodic boundary conditions apply
      // then move it to the other side of the lane
      // This is all local
      float frot = rot/180.0 * M_PI;
      pixx += x*cos(frot)-y*sin(frot);
      pixy += x*sin(frot)+y*cos(frot);
      if (pixx < 0 || pixy < 0) {
          y += 120 * 9;
      }
      if (pixx > 1080 || pixy > 1080) {
          y += 120 * 9;
      }
#endif
      painter->translate(x, y);
      paintCar();
      painter->restore();
    }
  }
}

void CustomOpenGLWidget::paintCar() {
  painter->save();
  painter->setPen(Qt::gray);
  painter->setBrush(QBrush(QColor(0, 255, 255)));
  painter->drawRoundedRect(-10, -17, 20, 24, 4, 4);
  painter->setPen(QPen(QColor(0, 255, 255), 1, Qt::SolidLine));
  painter->setBrush(QBrush(QColor(0, 155, 255)));
  painter->drawRoundedRect(-7, -15, 14, 15, 4, 4);
  painter->restore();
}
