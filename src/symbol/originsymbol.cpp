/**
 * @file   originsymbol.cpp
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

#include "originsymbol.h"

#include <QtWidgets>

OriginSymbol::OriginSymbol():
    Symbol("Origin", "Origin", P)
{
  m_rad = 9;
  setFlag(ItemIgnoresTransformations);
}

QRectF OriginSymbol::boundingRect() const
{
  return QRectF(-m_rad, -m_rad, m_rad * 2, m_rad * 2);
}

void OriginSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *, QWidget *)
{
  qreal srad = m_rad * 0.7;
  painter->setPen(QPen(m_pen.color(), 0));
  painter->setBrush(Qt::transparent);

  painter->drawEllipse(QPointF(0, 0), srad, srad);
  painter->drawLine(QPointF(-m_rad, 0), QPointF(m_rad, 0));
  painter->drawLine(QPointF(0, m_rad), QPointF(0, -m_rad));
  painter->drawLine(QPointF(-srad, -srad), QPointF(srad, srad));
  painter->drawLine(QPointF(srad, -srad), QPointF(-srad, srad));
}
