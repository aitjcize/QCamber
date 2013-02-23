#include "horizontalhexagonsymbol.h"

#include <QtGui>
#include <QRegExp>


HorizontalHexagonSymbol::HorizontalHexagonSymbol(QString def, Polarity polarity):
    Symbol(def, "hex_l([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  m_r = caps[3].toDouble() / 1000.0;

  painterPath();
}

QPainterPath HorizontalHexagonSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  m_cachedPath.moveTo( -m_w/2 + m_r, -m_h/2 );
  m_cachedPath.lineTo( -m_w/2, 0 );
  m_cachedPath.lineTo( -m_w/2 + m_r, m_h/2 );
  m_cachedPath.lineTo( m_w/2 - m_r, m_h/2 );
  m_cachedPath.lineTo( m_w/2, 0 );
  m_cachedPath.lineTo( m_w/2 - m_r, -m_h/2 );
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
