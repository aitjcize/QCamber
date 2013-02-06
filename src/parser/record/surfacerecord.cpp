#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"


void SurfaceRecord::initSymbol(void)
{
  symbol = new SurfaceSymbol(this);
}
