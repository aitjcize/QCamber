#include "surfacesymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

SurfaceSymbol::SurfaceSymbol(SurfaceRecord* rec):
  Symbol("surface", "surface", rec->polarity)
{
  m_dcode = rec->dcode;
  m_polygons = rec->polygons;

  painterPath();
}

QPainterPath SurfaceSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  for (QList<PolygonRecord*>::iterator it = m_polygons.begin();
      it != m_polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    m_cachedPath.addPath(rec->painterPath());
    /*
    if (rec->poly_type == PolygonRecord::I) {
      ipath.addPath(rec->painterPath());
    } else {
      ipath.addPath(rec->painterPath());
    }
    */
  }

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
