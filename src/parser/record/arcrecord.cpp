#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

QPainterPath ArcRecord::painterPath(void)
{
  Symbol* symbol = new ArcSymbol(this);
  QPainterPath path = symbol->painterPath();
  delete symbol;
  return path;
}

void ArcRecord::add(QGraphicsScene* scene)
{
  Symbol* symbol = new ArcSymbol(this);
  scene->addItem(symbol);
}
