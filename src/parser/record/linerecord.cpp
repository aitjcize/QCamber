#include <QDebug>
#include <QPainter>
#include <cmath>
#include <QMatrix>
#include "record.h"
#include "context.h"
#include "symbolfactory.h"

void LineRecord::initSymbol(void)
{
  symbol = new LineSymbol(this);
}
