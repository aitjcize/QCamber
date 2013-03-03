#include "squaresymbol.h"

#include <QtGui>
#include <QRegExp>


SquareSymbol::SquareSymbol(QString def, Polarity polarity):
    Symbol(def, "s([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_s = caps[1].toDouble() / 1000.0;

  painterPath();
}

QPainterPath SquareSymbol::painterPath(void)
{
  static bool first = true;
  QPainterPath m_cachedPath;

  m_cachedPath.addRect(-m_s / 2, -m_s / 2, m_s, m_s);

ret:
  if (first) {
    prepareGeometryChange();
    m_bounding = m_cachedPath.boundingRect();
    first = false;
  }

  return m_cachedPath;
}
