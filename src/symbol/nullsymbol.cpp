#include "nullsymbol.h"

#include <QtGui>
#include <QRegExp>


NullSymbol::NullSymbol(QString def, Polarity polarity):
    Symbol("null", "null([0-9.]+)", polarity), m_def(def)
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
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();


ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
