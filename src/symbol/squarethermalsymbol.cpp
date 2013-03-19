#include "squarethermalsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


SquareThermalSymbol::SquareThermalSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "s_ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_od = caps[1].toDouble() / 1000.0;
  m_id = caps[2].toDouble() / 1000.0;
  m_angle = caps[3].toDouble();
  m_num_spokes = caps[4].toInt();
  m_gap = caps[5].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath SquareThermalSymbol::painterPath(void)
{
  QPainterPath path;

  path.addRect(-m_od / 2, -m_od / 2, m_od, m_od);
  path.addRect(-m_id / 2, -m_id / 2, m_id, m_id);

  QPainterPath bar;
  bar.addRect(0, -m_gap / 2, m_od, m_gap);

  QPainterPath sub;

  QMatrix mat;
  mat.rotate(-m_angle);

  qreal angle_div = 360.0 / m_num_spokes;

  for (int i = 0; i < m_num_spokes; ++i) {
    sub.addPath(mat.map(bar));
    mat.rotate(-angle_div);
  }

  path = path.subtracted(sub);

  return path;
}
