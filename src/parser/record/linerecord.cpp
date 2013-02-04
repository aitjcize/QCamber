#include "record.h"

#include <QDebug>
#include <cmath>

void LineRecord::addShape(QPainterPath& path)
{
  path.moveTo(xs, ys);
  path.lineTo(xe, ye);
}

