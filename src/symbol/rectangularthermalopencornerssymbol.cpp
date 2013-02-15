#include "rectangularthermalopencornerssymbol.h"

#include <QtGui>
#include <QRegExp>

RectangularThermalOpenCornersSymbol::RectangularThermalOpenCornersSymbol(QString def, Polarity polarity):
    Symbol("rc_tho", "rc_tho([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  m_angle = caps[3].toDouble();
  m_num_spokes = caps[4].toInt();
  m_gap = caps[5].toDouble() / 1000.0;
  m_air_gap = caps[6].toDouble() / 1000.0;

  painterPath();
}

QPainterPath RectangularThermalOpenCornersSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  qreal a2r = M_PI / 180.0;
  qreal angle_div = 360.0 / m_num_spokes;
  QPainterPath sub;
  QMatrix mat;

  // From what we seen in Genesis 2000, num_spokes can only be 1, 2, 4
  // angle can only be multiple of 45
  if ((m_num_spokes != 1 && m_num_spokes != 2 && m_num_spokes != 4) ||
      ((int)m_angle % 45 != 0)) {
    goto ret;
  }

  m_cachedPath.addRect(-m_w / 2, -m_h / 2, m_w, m_h);
  m_cachedPath.addRect(-m_w / 2 + m_air_gap, -m_h / 2 + m_air_gap,
      m_w - 2 * m_air_gap, m_h - 2 * m_air_gap);

  if ((int)m_angle % 90 == 0) {
    QPainterPath bar;
    bar.addRect(0, -m_gap / 2, m_w / 2, m_gap);

    for (int i = 0; i < m_num_spokes; ++i) {
      sub.addPath(mat.map(bar));
      mat.rotate(-angle_div);
    }
  } else {
    qreal side = m_gap * qCos(M_PI / 4) + m_air_gap;
    qreal offset_w = (m_w - side) / 2, offset_h = (m_h - side) / 2;

    QPainterPath box;
    box.addRect(-side / 2, -side / 2, side, side);

    for (int i = 0; i < m_num_spokes; ++i) {
      QMatrix mat;
      mat.translate(offset_w * sign(qCos((m_angle + angle_div * i) * a2r)),
                    -offset_h * sign(qSin((m_angle + angle_div * i) * a2r)));
      sub.addPath(mat.map(box));
    }
  }

  m_cachedPath = m_cachedPath.subtracted(sub);

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
