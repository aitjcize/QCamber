#ifndef __SURFACESYMBOL_H__
#define __SURFACESYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class SurfaceSymbol: public Symbol {
public:
  SurfaceSymbol(SurfaceRecord* rec);

  virtual QString infoText(void);
  virtual QPainterPath painterPath(void);

private:
  int m_dcode;
  int m_holeCount;
  int m_islandCount;
  QList<PolygonRecord*> m_polygons;
};

#endif /* __SURFACESYMBOL_H__ */
