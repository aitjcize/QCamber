#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

extern Context ctx;

void PadRecord::addShape(QPainterPath& path, qreal ox, qreal oy)
{
  QString sym_name = ctx.cfds->symbolNameMap()[sym_num];
  Symbol* symbol = SymbolFactory::create(sym_name);
  symbol->setPos(ox + x, oy -y);
  symbol->addShape(path);
}

void PadRecord::paint(QPainter* painter)
{
  QString sym_name = ctx.cfds->symbolNameMap()[sym_num];
  Symbol* symbol = SymbolFactory::create(sym_name);
  symbol->setPos(x, y);
  ctx.cscene->addItem(symbol);
  // XXX: orient, polarity
}
