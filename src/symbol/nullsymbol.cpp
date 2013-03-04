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

  m_bounding = painterPath().boundingRect();
}

QPainterPath NullSymbol::painterPath(void)
{
  QPainterPath path;


  return path;
}
