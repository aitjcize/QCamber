#include "ovalsymbol.h"

#include <QtGui>
#include <QRegExp>


OvalSymbol::OvalSymbol(QString def, Polarity polarity):
    Symbol(def, "oval([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath OvalSymbol::painterPath(void)
{
  QPainterPath m_cachedPath;

  qreal x = -m_w / 2;
  qreal y = -m_h / 2;

  if (m_w > m_h) {
    qreal rad = m_h / 2;
    m_cachedPath.arcMoveTo(x, y, m_h, m_h, 90);
    m_cachedPath.arcTo(x, y, m_h, m_h, 270, -180);
    m_cachedPath.arcTo(x+m_w-m_h, y, m_h, m_h, 90, -180);
    m_cachedPath.lineTo(x+rad, y+m_h);
    m_cachedPath.closeSubpath();
  } else {
    qreal rad = m_w / 2;
    m_cachedPath.arcMoveTo(x, y, m_w, m_w, 90);
    m_cachedPath.arcTo(x, y, m_w, m_w, 180, -180);
    m_cachedPath.arcTo(x, y+m_h-m_w, m_w, m_w, 0, -180);
    m_cachedPath.lineTo(x, y+rad);
    m_cachedPath.closeSubpath();
  }

ret:

  return m_cachedPath;
}
