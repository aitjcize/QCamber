#include "record.h"

#include <cmath>

#include <QMatrix>
#include <QPainterPath>
#include <QTransform>

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
  symbol = SymbolFactory::create(sym_name, polarity);

  symbol->setPos(x, -y);

  if (orient >= M_0) {
    QTransform trans;
    trans.scale(-1, 1);
    symbol->setTransform(trans);
  }
  symbol->setRotation((orient % 4) * 90);
}
