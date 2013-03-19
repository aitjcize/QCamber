#include "surfacesymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

SurfaceSymbol::SurfaceSymbol(const SurfaceRecord* rec):
  Symbol("Surface", "Surface", rec->polarity, rec->attrib),
  m_islandCount(0), m_holeCount(0)
{
  m_dcode = rec->dcode;
  m_polygons = rec->polygons;

  m_bounding = painterPath().boundingRect();
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

QString SurfaceSymbol::longInfoText(void)
{
  QPointF c = m_bounding.center();
  QString result(
      "Surface\n\n"
      "XC\t= %1\n"
      "YC\t= %2\n"
      "Islands\t= %3\n"
      "Holes\t= %4\n"
      "PolygonRecord\t= %5\n"
  );
  return result \
    .arg(c.x()).arg(c.y()) \
    .arg(m_islandCount).arg(m_holeCount) \
    .arg((m_polarity == P)? "POS": "NEG");
}

QPainterPath SurfaceSymbol::painterPath(void)
{
  QPainterPath path;

  m_islandCount = 0;
  m_holeCount = 0;

  for (QList<PolygonRecord*>::iterator it = m_polygons.begin();
      it != m_polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    path.addPath(rec->painterPath());
    if (rec->poly_type == PolygonRecord::I) {
      ++m_islandCount;
    } else {
      ++m_holeCount;
    }
  }

  return path;
}
