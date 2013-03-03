#include "rectangularthermalsymbol.h"

#include <QtGui>
#include <QRegExp>


RectangularThermalSymbol::RectangularThermalSymbol(QString def, Polarity polarity):
    Symbol(def, "rc_ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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

QPainterPath RectangularThermalSymbol::painterPath(void)
{
  QPainterPath m_cachedPath;

  m_cachedPath.addRect(-m_w / 2, -m_h / 2, m_w, m_h);
  m_cachedPath.addRect(-m_w / 2 + m_air_gap, -m_h / 2 + m_air_gap,
      m_w - 2 * m_air_gap, m_h - 2 * m_air_gap);

  QPainterPath bar;
  bar.addRect(0, -m_gap / 2, m_w, m_gap);

  qreal a2r = M_PI / 180.0;
  QPainterPath sub;

  qreal angle_div = 360.0 / m_num_spokes;

  qreal ang = m_angle;
  for (int i = 0; i < m_num_spokes; ++i, ang += angle_div) {
    QMatrix mat;
    ang = qCeil(ang / 45) * 45.0;

    if ((int)ang % 90 != 0) {
      if (m_w > m_h) {
        mat.translate((m_w - m_h) / 2 * sign(qCos((ang) * a2r)), 0);
      } else {
        mat.translate(0, -(m_h - m_w) / 2 * sign(qSin((ang) * a2r)));
      }
    }
    mat.rotate(-ang);
    sub.addPath(mat.map(bar));
  }

  m_cachedPath = m_cachedPath.subtracted(sub);

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
