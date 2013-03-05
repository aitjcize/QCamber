#include "diamondsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


DiamondSymbol::DiamondSymbol(QString def, Polarity polarity):
    Symbol(def, "di([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath DiamondSymbol::painterPath(void)
{
  QPainterPath path;

  qreal x = -m_w / 2;
  qreal y = -m_h / 2;
  qreal wh = m_w / 2;
  qreal hh = m_h / 2;

  path.moveTo(x, y+hh);
  path.lineTo(x+wh, y);
  path.lineTo(x+m_w, y+hh);
  path.lineTo(x+wh, y+m_h);
  path.closeSubpath();

  return path;
}
