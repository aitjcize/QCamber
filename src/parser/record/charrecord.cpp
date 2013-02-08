#include "record.h"

#include <QtCore/qmath.h>

#include "fontparser.h"
#include "charsymbol.h"

CharLineRecord::CharLineRecord(const QStringList& param)
{
  int i = 0;
  xs = param[++i].toDouble();
  ys = param[++i].toDouble();
  xe = param[++i].toDouble();
  ye = param[++i].toDouble();
  polarity = (param[++i] == "P")? P: N;
  shape = (param[++i] == "R")? R: S;
  width = param[++i].toDouble();
}

QPainterPath CharLineRecord::painterPath(void)
{
  QPainterPath path;

  qreal radius = width / 2.0;
  qreal sx = xs, sy = ys;
  qreal ex = xe, ey = ye;
  qreal dx = ex - sx, dy = ey - sy;

  //make sure start is at left hand side of end
  if (xs > xe) {
    qreal tmp = xs;
    xs = xe;
    xe = tmp;
    tmp = ys;
    ys = ye;
    ye = tmp;
  }

  qreal a = qAtan2(dy, dx);
  qreal rsina = radius * qSin(a), rcosa = radius * qCos(a);

  path.moveTo(sx + rsina, -(sy - rcosa));
  path.lineTo(sx - rsina, -(sy + rcosa));
  path.lineTo(ex - rsina, -(ey + rcosa));
  path.lineTo(ex + rsina, -(ey - rcosa));
  if (shape == R) {
    path.addEllipse(QPointF(sx, -sy), radius, radius);
    path.addEllipse(QPointF(ex, -ey), radius, radius);
  } else {
    qreal radius2 = radius2 * 2;
    path.addRect(sx-radius, -sy-radius, radius2, radius2);
    path.addRect(ex-radius, -ey-radius, radius2, radius2);
  }
  path.closeSubpath();

  return path;
}

CharRecord::CharRecord(FontDataStore* ds, const QStringList& param):
  Record(ds)
{
  tchar = param[1].toAscii()[0];
}

void CharRecord::initSymbol()
{
  symbol = new CharSymbol(this);
}
