/**
 * @file   roundthermalsquaresymbol.cpp
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2012 - 2014 Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "roundthermalsquaresymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


RoundThermalSquareSymbol::RoundThermalSquareSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toLatin1());

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
  QPainterPath path;

  qreal _pie_angle = 360 / m_num_spokes;
  qreal _half_inner_gap_angle = R2D * (qAsin( m_gap / m_id ));
  qreal _half_outer_gap_angle = R2D * (qAsin( m_gap / m_od ));
  qreal _inner_start_angle = m_angle + _half_inner_gap_angle;
  qreal _inner_pie_angle = _pie_angle - 2 * _half_inner_gap_angle;
  qreal _outer_start_angle = m_angle + _half_outer_gap_angle;
  qreal _outer_pie_angle = _pie_angle - 2 * _half_outer_gap_angle;

  for( int pie_id= 0; pie_id != m_num_spokes; ++pie_id ){
    path.arcMoveTo( -m_od / 2, -m_od / 2, m_od, m_od, _outer_start_angle );
    path.arcTo( -m_od / 2, -m_od / 2, m_od, m_od, _outer_start_angle, _outer_pie_angle );
    path.arcTo( -m_id / 2, -m_id / 2, m_id, m_id, _inner_start_angle + _inner_pie_angle, 0 );
    path.arcTo( -m_id / 2, -m_id / 2, m_id, m_id, _inner_start_angle + _inner_pie_angle, -_inner_pie_angle );
    path.closeSubpath();
    _inner_start_angle += _pie_angle;
    _outer_start_angle += _pie_angle;
  }

  return path;
}
