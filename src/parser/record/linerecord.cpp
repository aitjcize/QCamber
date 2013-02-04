#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void LineRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  path.moveTo(ox + xs, oy - ys);
  path.lineTo(ox + xe, oy - ye);
}

void LineRecord::add(QGraphicsScene* scene)
{
  QPainterPath path;
  addShape(path, 0, 0);
  scene->addPath(path);
}
