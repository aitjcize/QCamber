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
  void addShape(QPainterPath& path);

private:
  Polarity polarity;
  int dcode;
  QList<PolygonRecord*> polygons;
  QRectF bounding;
};

#endif /* __SURFACESYMBOL_H__ */
