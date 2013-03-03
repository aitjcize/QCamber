#include "surfacesymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

SurfaceSymbol::SurfaceSymbol(SurfaceRecord* rec):
  Symbol("Surface", "Surface", rec->polarity)
{
  m_dcode = rec->dcode;
  m_polygons = rec->polygons;

  painterPath();
}

QString SurfaceSymbol::infoText(void)
{
  QPointF c = m_bounding.center();
  QString info = QString("Surface, XC=%1, YC=%2, Islands=%3, Holes=%4, %5") \
    .arg(c.x()).arg(c.y()) \
    .arg(m_islandCount).arg(m_holeCount) \
    .arg((m_polarity == P)? "POS": "NEG");
  return info;
}

QPainterPath SurfaceSymbol::painterPath(void)
{
  static bool first = true;
  QPainterPath m_cachedPath;

  for (QList<PolygonRecord*>::iterator it = m_polygons.begin();
      it != m_polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    m_cachedPath.addPath(rec->painterPath());
    if (rec->poly_type == PolygonRecord::I) {
      ++m_islandCount;
      //ipath.addPath(rec->painterPath());
    } else {
      ++m_holeCount;
      //ipath.addPath(rec->painterPath());
    }
  }

  if (first) {
    prepareGeometryChange();
    m_bounding = m_cachedPath.boundingRect();
    m_valid = true;
    first = false;
  }

  return m_cachedPath;
}
