#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

QPainterPath SurfaceRecord::painterPath(void)
{
  QPainterPath path;
  for (QList<PolygonRecord*>::iterator it = polygons.begin();
      it != polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    path.addPath(rec->painterPath());
    /*
    if (rec->poly_type == PolygonRecord::I) {
      rec->addShape(ipath);
    } else {
      rec->addShape(hpath);
    }
    */
  }
  return path;
}

void SurfaceRecord::add(QGraphicsScene* scene)
{
  Symbol* symbol = new SurfaceSymbol(this);
  scene->addItem(symbol);
}
