#ifndef CUSTOMOPENGLWIDGET_H
#define CUSTOMOPENGLWIDGET_H

#include <QOpenGLWidget>

class CustomOpenGLWidget : public QOpenGLWidget {

  Q_OBJECT

public:
  CustomOpenGLWidget(QWidget *Parent = 0);
  ~CustomOpenGLWidget();

protected:
  void paintEvent(QPaintEvent *event);

private:
  void paintGrid(QPainter &painter);
  void paintIntersectionGrid(QPainter &painter);
};

#endif // CUSTOMOPENGLWIDGET_H
