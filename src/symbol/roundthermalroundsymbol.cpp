/**
 * @file   roundthermalroundsymbol.cpp
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

#include "roundthermalroundsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


RoundThermalRoundSymbol::RoundThermalRoundSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "thr([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
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

QPainterPath RoundThermalRoundSymbol::painterPath(void)
{
  QPainterPath path;

  qreal _rad = (m_od - m_id) / 4;
  qreal _orad = (m_od + m_id) / 4;
  qreal _half_gap_angle = R2D * (qAtan2(m_gap / 2 + _rad, _orad));
  qreal _pie_angle = 360 / m_num_spokes;
  qreal _start_angle = m_angle + _half_gap_angle;
  qreal _span_angle = _pie_angle - 2 * _half_gap_angle;

  path.setFillRule(Qt::WindingFill);

  qreal _x, _y;
  for (int pie_id= 0; pie_id != m_num_spokes; ++pie_id) {
    path.arcMoveTo(-m_id / 2, -m_id / 2, m_id, m_id, _start_angle);
    path.arcTo(-m_id / 2, -m_id / 2, m_id, m_id, _start_angle,
        _span_angle);
    path.arcTo(-m_od / 2, -m_od / 2, m_od, m_od,
        _start_angle + _span_angle, -_span_angle);

    _x = _orad * qCos(_start_angle * D2R);
    _y = _orad * qSin(_start_angle * D2R);
    path.addEllipse(QPointF(_x, -_y), _rad, _rad);

    _x = _orad * qCos((_start_angle + _span_angle) * D2R);
    _y = _orad * qSin((_start_angle + _span_angle) * D2R);
    path.addEllipse(QPointF(_x, -_y), _rad, _rad);

    _start_angle += _pie_angle;
  }

  return path;
}
