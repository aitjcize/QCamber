#include "squarebutterflysymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


SquareButterflySymbol::SquareButterflySymbol(QString def, Polarity polarity):
    Symbol(def, "bfs([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_s = caps[1].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath SquareButterflySymbol::painterPath(void)
{
  QPainterPath path;

  path.addRect(-m_s/2, -m_s/2, m_s/2, m_s/2);
  path.addRect(0, 0, m_s/2, m_s/2);

  return path;
}
