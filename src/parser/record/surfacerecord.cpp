#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

QPainterPath SurfaceRecord::painterPath(void)
{
  Symbol* symbol = new SurfaceSymbol(this);
  QPainterPath path = symbol->painterPath();
  delete symbol;
  return path;
}

void SurfaceRecord::add(QGraphicsScene* scene)
{
  Symbol* symbol = new SurfaceSymbol(this);
  scene->addItem(symbol);
}
