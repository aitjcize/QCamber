#include "record.h"

#include <cmath>

#include <QMatrix>
#include <QPainterPath>
#include <QTransform>

#include "featuresparser.h"
#include "symbolfactory.h"

PadRecord::PadRecord(FeaturesDataStore* ds, const QStringList& param,
    const AttribData& attr):
  Record(ds, attr)
{
  int i = 0;
  x = param[++i].toDouble();
  y = param[++i].toDouble();
  sym_num = param[++i].toInt();
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
  orient = (Orient)param[++i].toInt();
  sym_name = ds->symbolNameMap()[sym_num];
}

Symbol* PadRecord::createSymbol(void) const
{
  Symbol* symbol = SymbolFactory::create(sym_name, polarity);
  symbol->setPos(x, -y);

  if (orient >= M_0) {
    QTransform trans;
    trans.scale(-1, 1);
    symbol->setTransform(trans);
  }
  symbol->setRotation((orient % 4) * 90);
  return symbol;
}
