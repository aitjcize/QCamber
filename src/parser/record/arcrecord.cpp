#include <QDebug>
#include <QPainter>
#include <cmath>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

void ArcRecord::initSymbol(void)
{
  symbol = new ArcSymbol(this);
}
