/**
 * @file   squareroundthermalsymbol.cpp
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

#include "squareroundthermalsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"

#include "context.h"

SquareRoundThermalSymbol::SquareRoundThermalSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "sr_ths([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
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

QPainterPath SquareRoundThermalSymbol::painterPath(void)
{
  QPainterPath path;

  path.addRect(-m_od / 2, -m_od / 2, m_od, m_od);
  path.addEllipse(-m_id / 2, -m_id / 2, m_id, m_id);

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
  //path = path.subtracted(sub);

  return path;
}

void SquareRoundThermalSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (m_polarity == P) {
    painter->setClipPath(m_sub);
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(painterPath());
  } else {
    painter->setClipPath(m_sub);
    painter->setPen(QPen(ctx.bg_color, 0));
    painter->setBrush(ctx.bg_color);
    painter->drawPath(painterPath());
  }
}
