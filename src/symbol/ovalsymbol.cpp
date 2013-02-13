#include "ovalsymbol.h"

#include <QtGui>
#include <QRegExp>

OvalSymbol::OvalSymbol(QString def, Polarity polarity):
    Symbol("oval", "oval([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  painterPath();
}

QPainterPath OvalSymbol::painterPath(void)
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

  if (w > h) {
    qreal rad = h / 2;
    m_cachedPath.arcMoveTo(x, y, h, h, 90);
    m_cachedPath.arcTo(x, y, h, h, 270, -180);
    m_cachedPath.arcTo(x+w-h, y, h, h, 90, -180);
    m_cachedPath.lineTo(x+rad, y+h);
    m_cachedPath.closeSubpath();
  } else {
    qreal rad = w / 2;
    m_cachedPath.arcMoveTo(x, y, w, w, 90);
    m_cachedPath.arcTo(x, y, w, w, 180, -180);
    m_cachedPath.arcTo(x, y+h-w, w, w, 0, -180);
    m_cachedPath.lineTo(x, y+rad);
    m_cachedPath.closeSubpath();
  }

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
