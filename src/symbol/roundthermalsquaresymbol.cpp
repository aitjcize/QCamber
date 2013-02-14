#include "roundthermalsquaresymbol.h"

#include <QtGui>
#include <QRegExp>

RoundThermalSquareSymbol::RoundThermalSquareSymbol(QString def, Polarity polarity):
    Symbol("ths", "ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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

QPainterPath RoundThermalSquareSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  qreal _pie_angle = 360 / m_num_spokes;
  qreal _half_inner_gap_angle = radToAngle( qAsin( m_gap / m_id ) );
  qreal _half_outer_gap_angle = radToAngle( qAsin( m_gap / m_od ) );
  qreal _inner_start_angle = m_angle + _half_inner_gap_angle;
  qreal _inner_pie_angle = _pie_angle -  _half_inner_gap_angle;
  qreal _outer_start_angle = m_angle + _half_outer_gap_angle;
  qreal _outer_pie_angle = _pie_angle - _half_outer_gap_angle;

  for( int pie_id= 0; pie_id != m_num_spokes; ++pie_id ){
    m_cachedPath.arcMoveTo( -m_od / 2, -m_od / 2, m_od, m_od, _outer_start_angle );
    m_cachedPath.arcTo( -m_od / 2, -m_od / 2, m_od, m_od, _outer_start_angle, _outer_pie_angle );
    m_cachedPath.arcTo( -m_id / 2, -m_id / 2, m_id, m_id, _inner_start_angle + _inner_pie_angle, 0 );
    m_cachedPath.arcTo( -m_id / 2, -m_id / 2, m_id, m_id, _inner_start_angle + _inner_pie_angle, -_inner_pie_angle );
    m_cachedPath.closeSubpath();
    _inner_start_angle += _pie_angle;
    _outer_start_angle += _pie_angle;
  } 
  /*
  */

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
