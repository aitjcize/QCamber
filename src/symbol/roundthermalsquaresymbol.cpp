#include "roundthermalsquaresymbol.h"

#include <QtGui>
#include <QRegExp>


RoundThermalSquareSymbol::RoundThermalSquareSymbol(QString def, Polarity polarity):
    Symbol(def, "ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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

QPainterPath RoundThermalSquareSymbol::painterPath(void)
{
  QPainterPath m_cachedPath;

  qreal a2r = M_PI / 180.0, r2a = 180.0 / M_PI;
  qreal _pie_angle = 360 / m_num_spokes;
  qreal _half_inner_gap_angle = r2a * (qAsin( m_gap / m_id ));
  qreal _half_outer_gap_angle = r2a * (qAsin( m_gap / m_od ));
  qreal _inner_start_angle = m_angle + _half_inner_gap_angle;
  qreal _inner_pie_angle = _pie_angle - 2 * _half_inner_gap_angle;
  qreal _outer_start_angle = m_angle + _half_outer_gap_angle;
  qreal _outer_pie_angle = _pie_angle - 2 * _half_outer_gap_angle;

  for( int pie_id= 0; pie_id != m_num_spokes; ++pie_id ){
    m_cachedPath.arcMoveTo( -m_od / 2, -m_od / 2, m_od, m_od, _outer_start_angle );
    m_cachedPath.arcTo( -m_od / 2, -m_od / 2, m_od, m_od, _outer_start_angle, _outer_pie_angle );
    m_cachedPath.arcTo( -m_id / 2, -m_id / 2, m_id, m_id, _inner_start_angle + _inner_pie_angle, 0 );
    m_cachedPath.arcTo( -m_id / 2, -m_id / 2, m_id, m_id, _inner_start_angle + _inner_pie_angle, -_inner_pie_angle );
    m_cachedPath.closeSubpath();
    _inner_start_angle += _pie_angle;
    _outer_start_angle += _pie_angle;
  }

ret:

  return m_cachedPath;
}
