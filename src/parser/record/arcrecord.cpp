#include "record.h"

#include "featuresparser.h"
#include "arcsymbol.h"

ArcRecord::ArcRecord(FeaturesDataStore* ds, const QStringList& param):
  Record(ds)
{
  int i = 0;
  xs = param[++i].toDouble();
  ys = param[++i].toDouble();
  xe = param[++i].toDouble();
  ye = param[++i].toDouble();
  xc = param[++i].toDouble();
  yc = param[++i].toDouble();
  sym_num = param[++i].toInt();
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
  cw = (param[++i] == "Y");
  symbol = new ArcSymbol(this);
}
