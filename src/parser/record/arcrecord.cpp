#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void ArcRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  Symbol* symbol = new ArcSymbol(this);
  symbol->setPos(ox, oy);
  symbol->addShape(path);
}

void ArcRecord::add(QGraphicsScene* scene)
{
  Symbol* symbol = new ArcSymbol(this);
  scene->addItem(symbol);
}
