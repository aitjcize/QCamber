#include "butterflysymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


ButterflySymbol::ButterflySymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "bfr([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_r = caps[1].toDouble() / 1000.0 / 2.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath ButterflySymbol::painterPath(void)
{
  QPainterPath path;

  qreal m_d = 2.0 * m_r;
  path.moveTo( 0, 0 );
  path.arcTo( -m_r, -m_r, m_d, m_d, 90, 90 );
  path.moveTo( 0, 0 );
  path.arcTo( -m_r, -m_r, m_d, m_d, 0, -90 );
  path.closeSubpath();

  return path;
}
