#include "nullsymbol.h"

#include <QtGui>
#include <QRegExp>


NullSymbol::NullSymbol(QString def, Polarity polarity):
    Symbol(def, "null([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_ext = caps[1].toInt();

  painterPath();
}

QPainterPath NullSymbol::painterPath(void)
{
  QPainterPath m_cachedPath;


ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
