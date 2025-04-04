/**
 * @file   ovalsymbol.cpp
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

#include "ovalsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


OvalSymbol::OvalSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "oval([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toLatin1());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath OvalSymbol::painterPath(void)
{
  QPainterPath path;

  qreal x = -m_w / 2;
  qreal y = -m_h / 2;

  if (m_w > m_h) {
    qreal rad = m_h / 2;
    path.arcMoveTo(x, y, m_h, m_h, 90);
    path.arcTo(x, y, m_h, m_h, 270, -180);
    path.arcTo(x+m_w-m_h, y, m_h, m_h, 90, -180);
    path.lineTo(x+rad, y+m_h);
    path.closeSubpath();
  } else {
    qreal rad = m_w / 2;
    path.arcMoveTo(x, y, m_w, m_w, 90);
    path.arcTo(x, y, m_w, m_w, 180, -180);
    path.arcTo(x, y+m_h-m_w, m_w, m_w, 0, -180);
    path.lineTo(x, y+rad);
    path.closeSubpath();
  }

  return path;
}
