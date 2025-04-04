/**
 * @file   rectangularthermalsymbol.cpp
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

#include "rectangularthermalsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


RectangularThermalSymbol::RectangularThermalSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "rc_ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toLatin1());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  m_angle = caps[3].toDouble();
  m_num_spokes = caps[4].toInt();
  m_gap = caps[5].toDouble() / 1000.0;
  m_air_gap = caps[6].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath RectangularThermalSymbol::painterPath(void)
{
  QPainterPath path;

  path.addRect(-m_w / 2, -m_h / 2, m_w, m_h);
  path.addRect(-m_w / 2 + m_air_gap, -m_h / 2 + m_air_gap,
      m_w - 2 * m_air_gap, m_h - 2 * m_air_gap);

  QPainterPath bar;
  bar.addRect(0, -m_gap / 2, m_w, m_gap);

  QPainterPath sub;

  qreal angle_div = 360.0 / m_num_spokes;

  qreal ang = m_angle;
  for (int i = 0; i < m_num_spokes; ++i, ang += angle_div) {
    QMatrix mat;
    ang = qCeil(ang / 45) * 45.0;

    if ((int)ang % 90 != 0) {
      if (m_w > m_h) {
        mat.translate((m_w - m_h) / 2 * sign(qCos((ang) * D2R)), 0);
      } else {
        mat.translate(0, -(m_h - m_w) / 2 * sign(qSin((ang) * D2R)));
      }
    }
    mat.rotate(-ang);
    sub.addPath(mat.map(bar));
  }

  path = path.subtracted(sub);

  return path;
}
