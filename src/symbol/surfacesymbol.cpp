#include "surfacesymbol.h"

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

#include <QtGui>
#include <QRegExp>

#include "context.h"

extern Context ctx;

SurfaceSymbol::SurfaceSymbol(SurfaceRecord* rec): Symbol("user", "user")
{
  m_polarity = rec->polarity;
  m_dcode = rec->dcode;
  m_polygons = rec->polygons;
}

QRectF SurfaceSymbol::boundingRect() const
{
  return m_bounding;
}

void SurfaceSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  QPainterPath path;
  addShape(path);

  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawPath(path);

  m_bounding = path.boundingRect();
}

void SurfaceSymbol::addShape(QPainterPath& path)
{
  for (QList<PolygonRecord*>::iterator it = m_polygons.begin();
      it != m_polygons.end(); ++it) {
    PolygonRecord* rec = (*it);
    rec->addShape(path, pos().x(), -pos().y());
    /*
    if (rec->poly_type == PolygonRecord::I) {
      rec->addShape(ipath);
    } else {
      rec->addShape(hpath);
    }
    */
  }
}
