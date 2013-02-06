#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

QPainterPath PadRecord::painterPath(void)
{
  QString sym_name = ds->symbolNameMap()[sym_num];
  Symbol* symbol = SymbolFactory::create(sym_name);
  QPainterPath path = symbol->painterPath();
  path.translate(x, -y);

  delete symbol;
  return path;
  // XXX: rotation
}

void PadRecord::add(QGraphicsScene* scene)
{
  QString sym_name = ds->symbolNameMap()[sym_num];
  Symbol* symbol = SymbolFactory::create(sym_name);
  symbol->setPos(x, -y);
  scene->addItem(symbol);

  symbol->rotate((orient % 4) * -90);
  if (orient >= M_0) {
    symbol->scale(1, -1);
  }
}
