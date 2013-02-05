#ifndef __SURFACESYMBOL_H__
#define __SURFACESYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class SurfaceSymbol: public Symbol {
public:
  SurfaceSymbol(SurfaceRecord* rec);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);
  QPainterPath painterPath(void);

private:
  Polarity m_polarity;
  int m_dcode;
  QList<PolygonRecord*> m_polygons;
  QRectF m_bounding;
};

#endif /* __SURFACESYMBOL_H__ */
