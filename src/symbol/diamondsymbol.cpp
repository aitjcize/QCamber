#include "diamondsymbol.h"

#include <QtGui>
#include <QRegExp>


DiamondSymbol::DiamondSymbol(QString def, Polarity polarity):
    Symbol(def, "di([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  painterPath();
}

QPainterPath DiamondSymbol::painterPath(void)
{
  QPainterPath m_cachedPath;

  qreal x = -m_w / 2;
  qreal y = -m_h / 2;
  qreal wh = m_w / 2;
  qreal hh = m_h / 2;

  m_cachedPath.moveTo(x, y+hh);
  m_cachedPath.lineTo(x+wh, y);
  m_cachedPath.lineTo(x+m_w, y+hh);
  m_cachedPath.lineTo(x+wh, y+m_h);
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
