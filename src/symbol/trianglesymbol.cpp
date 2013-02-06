#include "trianglesymbol.h"

#include <QtGui>
#include <QRegExp>

TriangleSymbol::TriangleSymbol(QString def):
    Symbol("tri", "tri([0-9.]+)x([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_base = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  painterPath();
}

QPainterPath TriangleSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_valid = true;

  //The co-ordinates of y needs to be flipped
  //due to it is screen co-ordination ( increase from top to down )
  m_cachedPath.moveTo(0, - m_h / 2);
  m_cachedPath.lineTo(- m_base / 2, m_h / 2);
  m_cachedPath.lineTo(m_base / 2, m_h / 2);
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
