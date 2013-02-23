#include "halfovalsymbol.h"

#include <QtGui>
#include <QRegExp>


HalfOvalSymbol::HalfOvalSymbol(QString def, Polarity polarity):
    Symbol("oval_h", "oval_h([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  painterPath();
}

QPainterPath HalfOvalSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  if (m_w > m_h) {
    qreal rad = m_h / 2;
    m_cachedPath.moveTo(rad, -rad);
    m_cachedPath.arcTo(0, -m_h/2, m_h, m_h, 90, -180);
    m_cachedPath.lineTo(m_h - m_w, m_h/2);
    m_cachedPath.lineTo(m_h - m_w, -m_h/2);
    m_cachedPath.closeSubpath();
  } else {
    qreal rad = m_w / 2;
    m_cachedPath.moveTo(rad, -rad);
    m_cachedPath.arcTo(-m_w/2, -m_w, m_w, m_w, 0, 180);
    m_cachedPath.lineTo(-m_w/2, m_h - m_w);
    m_cachedPath.lineTo(m_w/2, m_h - m_w);
    m_cachedPath.closeSubpath();
  }

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
