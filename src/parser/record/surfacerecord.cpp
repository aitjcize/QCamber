#include "record.h"

#include <QDebug>
#include <cmath>

void SurfaceRecord::addShape(QPainterPath& path)
{
  for (QList<PolygonRecord*>::iterator it = polygons.begin();
      it != polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    rec->addShape(path);
  }
}

