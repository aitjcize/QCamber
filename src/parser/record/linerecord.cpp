#include <QDebug>
#include <QPainter>
#include <cmath>
#include <QMatrix>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void LineRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  Symbol* symbol = new LineSymbol(this);
  symbol->setPos(ox, oy);
  symbol->addShape(path);
}

void LineRecord::add(QGraphicsScene* scene)
{
  Symbol* symbol = new LineSymbol(this);
  scene->addItem(symbol);
}
