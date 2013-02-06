#ifndef __SURFACESYMBOL_H__
#define __SURFACESYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class SurfaceSymbol: public Symbol {
public:
  SurfaceSymbol(SurfaceRecord* rec);

  QPainterPath painterPath(void);

private:
  Polarity m_polarity;
  int m_dcode;
  QList<PolygonRecord*> m_polygons;
};

#endif /* __SURFACESYMBOL_H__ */
