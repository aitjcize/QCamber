#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

void PadRecord::initSymbol(void)
{
  QString sym_name = ds->symbolNameMap()[sym_num];
  symbol = SymbolFactory::create(sym_name);
}

QPainterPath PadRecord::painterPath(void)
{
  QPainterPath path = symbol->painterPath();
  path.translate(x, -y);

  return path;
  // XXX: rotation
}

void PadRecord::add(QGraphicsScene* scene)
{
  symbol->setPos(x, -y);
  scene->addItem(symbol);

  symbol->rotate((orient % 4) * -90);
  if (orient >= M_0) {
    symbol->scale(1, -1);
  }
}
