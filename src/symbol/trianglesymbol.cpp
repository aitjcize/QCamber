#include "trianglesymbol.h"

#include <QtGui>
#include <QRegExp>


TriangleSymbol::TriangleSymbol(QString def, Polarity polarity):
    Symbol(def, "tri([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_base = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath TriangleSymbol::painterPath(void)
{
  QPainterPath m_cachedPath;

  //The co-ordinates of y needs to be flipped
  //due to it is screen co-ordination ( increase from top to down )
  m_cachedPath.moveTo(0, - m_h / 2);
  m_cachedPath.lineTo(- m_base / 2, m_h / 2);
  m_cachedPath.lineTo(m_base / 2, m_h / 2);
  m_cachedPath.closeSubpath();

ret:

  return m_cachedPath;
}
