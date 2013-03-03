#include "record.h"

#include <QtCore/qmath.h>

#include "fontparser.h"

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

QPainterPath CharLineRecord::painterPath(qreal width_factor)
{
  QPainterPath path;

  qreal radius = width * width_factor / 2.0;
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
    qreal radius2 = radius * 2;
    path.addRect(sx-radius, -sy-radius, radius2, radius2);
    path.addRect(ex-radius, -ey-radius, radius2, radius2);
  }
  path.closeSubpath();

  return path;
}

CharRecord::CharRecord(FontDataStore* ds, const QStringList& param): ds(ds)
{
  tchar = param[1].toAscii()[0];
}

CharRecord::~CharRecord()
{
  for (QList<CharLineRecord*>::iterator it = lines.begin();
      it != lines.end(); ++it) {
    delete *it;
  }
}

QPainterPath CharRecord::painterPath(qreal width_factor)
{
  QPainterPath path;

  path.setFillRule(Qt::WindingFill);

  for (QList<CharLineRecord*>::iterator it = lines.begin();
      it != lines.end(); ++it) {
    CharLineRecord* rec = (*it);
    path.addPath(rec->painterPath(width_factor));
  }

  return path;
}
