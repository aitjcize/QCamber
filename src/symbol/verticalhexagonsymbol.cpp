#include "verticalhexagonsymbol.h"

#include <QtGui>
#include <QRegExp>


VerticalHexagonSymbol::VerticalHexagonSymbol(QString def, Polarity polarity):
    Symbol(def, "hex_s([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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

QPainterPath VerticalHexagonSymbol::painterPath(void)
{
  QPainterPath m_cachedPath;

  m_cachedPath.moveTo( 0, -m_h/2 );
  m_cachedPath.lineTo( -m_w/2, -m_h/2 + m_r );
  m_cachedPath.lineTo( -m_w/2, m_h/2 - m_r );
  m_cachedPath.lineTo( 0, m_h/2 );
  m_cachedPath.lineTo( m_w/2, m_h/2 - m_r );
  m_cachedPath.lineTo( m_w/2, -m_h/2 + m_r );
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
