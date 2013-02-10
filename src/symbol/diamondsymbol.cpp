#include "diamondsymbol.h"

#include <QtGui>
#include <QRegExp>

DiamondSymbol::DiamondSymbol(QString def, Polarity polarity):
    Symbol("di", "di([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  QRectF rect(-m_w / 2, -m_h / 2, m_w, m_h);
  QRectF r = rect.normalized();

  if (r.isNull())
    return m_cachedPath;

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();
  qreal wh = w / 2;
  qreal hh = h / 2;

  m_cachedPath.moveTo(x, y+hh);
  m_cachedPath.lineTo(x+wh, y);
  m_cachedPath.lineTo(x+w, y+hh);
  m_cachedPath.lineTo(x+wh, y+h);
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
