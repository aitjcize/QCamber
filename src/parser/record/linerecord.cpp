#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void LineRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  path.moveTo(xs, ys);
  path.lineTo(xe, ye);
}

void LineRecord::paint(QPainter *painter)
{
}
