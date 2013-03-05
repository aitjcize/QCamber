#include "holesymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


HoleSymbol::HoleSymbol(QString def, Polarity polarity):
    Symbol(def, "hole([0-9.]+)x([pnv])x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_r = caps[1].toDouble() / 1000.0 / 2;
  m_p = caps[2];
  m_tp = caps[3].toDouble() / 1000.0;
  m_tm = caps[4].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath HoleSymbol::painterPath(void)
{
  QPainterPath path;

  path.addEllipse(QPointF(0, 0), m_r, m_r);

  return path;
}
