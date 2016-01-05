#ifndef CUSTOMOPENGLWIDGET_H
#define CUSTOMOPENGLWIDGET_H

#include "car.h"
#include "intersection.h"

#include <QOpenGLWidget>
#include <QColor>

class CustomOpenGLWidget : public QOpenGLWidget {

  Q_OBJECT

public:
  CustomOpenGLWidget(QWidget *Parent = 0);
  ~CustomOpenGLWidget();

public slots:
  void setState(QVector<Intersection *> intersections);

protected:
  void paintEvent(QPaintEvent *event);

private:
  QPainter *painter;
  void paintGrid();
  void paintIntersectionGrid(int intersection);
  void paintCars();
  void paintCar();

  QColor getLightColor(int intersection, int lane);

  QVector<Intersection *> intersections;
};

#endif // CUSTOMOPENGLWIDGET_H
