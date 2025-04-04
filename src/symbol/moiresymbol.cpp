/**
 * @file   moiresymbol.cpp
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

#include "moiresymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"

#include "context.h"

MoireSymbol::MoireSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "moire([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toLatin1());

  QStringList caps = rx.capturedTexts();
  m_rw = caps[1].toDouble() / 1000.0;
  m_rg = caps[2].toDouble() / 1000.0;
  m_nr = caps[3].toInt();
  m_lw = caps[4].toDouble() / 1000.0;
  m_ll = caps[5].toDouble() / 1000.0;
  m_la = caps[6].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath MoireSymbol::painterPath(void)
{
  QPainterPath path;

  m_circlePath = QPainterPath();
  qreal rad = m_rw;
  m_circlePath.addEllipse(QPointF(0, 0), m_rw / 2, m_rw / 2);

  for (int i = 0; i < m_nr; ++i) {
    rad += m_rg - m_rw / 2;
    m_circlePath.addEllipse(QPointF(0, 0), rad, rad);
    rad += m_rw;
    m_circlePath.addEllipse(QPointF(0, 0), rad, rad);
  }

  qreal r = m_lw / 2;

  m_linePath = QPainterPath();
  m_linePath.setFillRule(Qt::WindingFill);

  m_linePath.addRect(-m_ll / 2, -m_lw / 2, m_ll, m_lw);
  m_linePath.addRect(-m_lw / 2, -m_ll / 2, m_lw, m_ll);
  m_linePath.addEllipse(QPointF(-m_ll / 2, 0), r, r);
  m_linePath.addEllipse(QPointF(m_ll / 2, 0), r, r);
  m_linePath.addEllipse(QPointF(0, -m_ll/2), r, r);
  m_linePath.addEllipse(QPointF(0, m_ll/2), r, r);

  path = m_circlePath;
  path.addPath(m_linePath);

  return path;
}

void MoireSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (m_polarity == P) {
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
  } else {
    painter->setPen(QPen(ctx.bg_color, 0));
    painter->setBrush(ctx.bg_color);
  }

  painterPath();
  painter->drawPath(m_circlePath);
  painter->drawPath(m_linePath);
}
