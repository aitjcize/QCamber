#include <QDebug>
#include <QPainter>
#include <cmath>
#include <QMatrix>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"


QPainterPath LineRecord::painterPath(void)
{
  Symbol* symbol = new LineSymbol(this);
  QPainterPath path = symbol->painterPath();
  delete symbol;
  return path;
}

void LineRecord::add(QGraphicsScene* scene)
{
  Symbol* symbol = new LineSymbol(this);
  scene->addItem(symbol);
}
