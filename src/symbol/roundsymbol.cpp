#include "roundsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


RoundSymbol::RoundSymbol(QString def, Polarity polarity):
    Symbol(def, "r([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_r = caps[1].toDouble() / 1000.0 / 2.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath RoundSymbol::painterPath(void)
{
  QPainterPath path;

  path.addEllipse(QPointF(0, 0), m_r, m_r);

  return path;
}
