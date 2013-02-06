#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"


SurfaceRecord::SurfaceRecord(FeaturesDataStore* ds, const QStringList& param):
  Record(ds)
{
  int i = 0;
  polarity = (param[++i] == "P")? P: N;
  dcode = param[++i].toInt();
}

void SurfaceRecord::initSymbol(void)
{
  symbol = new SurfaceSymbol(this);
}
