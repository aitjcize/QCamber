#include "butterflysymbol.h"

#include <QtGui>
#include <QRegExp>


ButterflySymbol::ButterflySymbol(QString def, Polarity polarity):
    Symbol(def, "bfr([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_r = caps[1].toDouble() / 1000.0 / 2.0;

  painterPath();
}

QPainterPath ButterflySymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  qreal m_d = 2.0 * m_r;
  m_cachedPath.moveTo( 0, 0 );
  m_cachedPath.arcTo( -m_r, -m_r, m_d, m_d, 90, 90 );
  m_cachedPath.moveTo( 0, 0 );
  m_cachedPath.arcTo( -m_r, -m_r, m_d, m_d, 0, -90 );
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
