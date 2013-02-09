#include "record.h"

#include <cmath>

#include <QPainterPath>
#include <QMatrix>

#include "featuresparser.h"
#include "symbolfactory.h"

PadRecord::PadRecord(FeaturesDataStore* ds, const QStringList& param):
  Record(ds)
{
  int i = 0;
  x = param[++i].toDouble();
  y = param[++i].toDouble();
  sym_num = param[++i].toInt();
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
  orient = (Orient)param[++i].toInt();
  QString sym_name = ds->symbolNameMap()[sym_num];
  symbol = SymbolFactory::create(sym_name);
}

QPainterPath PadRecord::painterPath(void)
{
  QPainterPath path = symbol->painterPath();
  path.translate(x, -y);

  qreal rad = (orient % 4) * 90;
  QMatrix mat;
  if (orient >= M_0) {
    mat.scale(-1, 1);
  }
  mat.rotate(rad);
  return mat.map(path);
}

void PadRecord::add(QGraphicsScene* scene)
{
  symbol->setPos(x, -y);
  scene->addItem(symbol);

  if (orient >= M_0) {
    symbol->scale(-1, 1);
  }
  symbol->rotate((orient % 4) * 90);
}
