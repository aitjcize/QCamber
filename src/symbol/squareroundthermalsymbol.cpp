#include "squareroundthermalsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "context.h"

SquareRoundThermalSymbol::SquareRoundThermalSymbol(QString def, Polarity polarity):
    Symbol(def, "sr_ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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

  painterPath();
}

QPainterPath SquareRoundThermalSymbol::painterPath(void)
{
  static bool first = true;
  QPainterPath m_cachedPath;

  m_cachedPath.addRect(-m_od / 2, -m_od / 2, m_od, m_od);
  m_cachedPath.addEllipse(-m_id / 2, -m_id / 2, m_id, m_id);

  QPainterPath bar;
  bar.addRect(0, -m_gap / 2, m_od / qSqrt(1.8), m_gap);

  QMatrix mat;
  mat.rotate(-m_angle);

  qreal angle_div = 360.0 / m_num_spokes;

  m_sub = QPainterPath();
  m_sub.addRect(-m_od / 2 * 1.1, -m_od / 2 * 1.1, m_od * 1.1, m_od * 1.1);
  for (int i = 0; i < m_num_spokes; ++i) {
    m_sub.addPath(mat.map(bar));
    mat.rotate(-angle_div);
  }

  // Simple subtraction will not work since QPainterPath::subtracted will
  // flatten the circle. We override paint to fix it.
  //m_cachedPath = m_cachedPath.subtracted(sub);

ret:
  if (first) {
    prepareGeometryChange();
    m_bounding = m_cachedPath.boundingRect();
    first = false;
  }

  return m_cachedPath;
}

void SquareRoundThermalSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPainterPath m_cachedPath;

  if (m_polarity == P) {
    painter->setClipPath(m_sub);
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(m_cachedPath);
  } else {
    painter->setClipPath(m_sub);
    painter->setPen(QPen(ctx.bg_color, 0));
    painter->setBrush(ctx.bg_color);
    painter->drawPath(m_cachedPath);
  }
}
