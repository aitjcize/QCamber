#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void SurfaceRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  for (QList<PolygonRecord*>::iterator it = polygons.begin();
      it != polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    rec->addShape(path, ox, oy);
    /*
    if (rec->poly_type == PolygonRecord::I) {
      rec->addShape(ipath);
    } else {
      rec->addShape(hpath);
    }
    */
  }
}

void SurfaceRecord::paint(QPainter* painter)
{
}
