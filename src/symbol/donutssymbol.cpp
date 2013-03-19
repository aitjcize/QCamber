#include "donutssymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


DonutSSymbol::DonutSSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "donut_s([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_od = caps[1].toDouble() / 1000.0;
  m_id = caps[2].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath DonutSSymbol::painterPath(void)
{
  QPainterPath path;

  path.addRect(-m_od / 2, -m_od / 2, m_od, m_od);
  path.addRect(-m_id / 2, -m_id / 2, m_id, m_id);

  return path;
}
