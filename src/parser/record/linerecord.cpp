#include "record.h"

#include <cmath>

#include "featuresparser.h"
#include "linesymbol.h"

LineRecord::LineRecord(FeaturesDataStore* ds, const QStringList& param,
    const AttribData& attr):
  Record(ds, attr)
{
  int i = 0;
  xs = param[++i].toDouble();
  ys = param[++i].toDouble();
  xe = param[++i].toDouble();
  ye = param[++i].toDouble();
  sym_num = param[++i].toInt();
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
}

Symbol* LineRecord::createSymbol(void) const
{
  return new LineSymbol(this);
}
