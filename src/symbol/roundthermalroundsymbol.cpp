#include "roundthermalroundsymbol.h"

#include <QtGui>
#include <QRegExp>


RoundThermalRoundSymbol::RoundThermalRoundSymbol(QString def, Polarity polarity):
    Symbol(def, "thr([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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

QPainterPath RoundThermalRoundSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  qreal a2r = M_PI / 180.0, r2a = 180.0 / M_PI;
  qreal _rad = (m_od - m_id) / 4;
  qreal _orad = (m_od + m_id) / 4;
  qreal _half_gap_angle = r2a * (qAtan2(m_gap / 2 + _rad, _orad));
  qreal _pie_angle = 360 / m_num_spokes;
  qreal _start_angle = m_angle + _half_gap_angle;
  qreal _span_angle = _pie_angle - 2 * _half_gap_angle;

  m_cachedPath.setFillRule(Qt::WindingFill);

  qreal _x, _y;
  for (int pie_id= 0; pie_id != m_num_spokes; ++pie_id) {
    m_cachedPath.arcMoveTo(-m_id / 2, -m_id / 2, m_id, m_id, _start_angle);
    m_cachedPath.arcTo(-m_id / 2, -m_id / 2, m_id, m_id, _start_angle,
        _span_angle);
    m_cachedPath.arcTo(-m_od / 2, -m_od / 2, m_od, m_od,
        _start_angle + _span_angle, -_span_angle);

    _x = _orad * qCos(_start_angle * a2r);
    _y = _orad * qSin(_start_angle * a2r);
    m_cachedPath.addEllipse(QPointF(_x, -_y), _rad, _rad);

    _x = _orad * qCos((_start_angle + _span_angle) * a2r);
    _y = _orad * qSin((_start_angle + _span_angle) * a2r);
    m_cachedPath.addEllipse(QPointF(_x, -_y), _rad, _rad);

    _start_angle += _pie_angle;
  }

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
