/**
 * @file   butterflysymbol.cpp
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

#include "butterflysymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


ButterflySymbol::ButterflySymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "bfr([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toLatin1());

  QStringList caps = rx.capturedTexts();
  m_r = caps[1].toDouble() / 1000.0 / 2.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath ButterflySymbol::painterPath(void)
{
  QPainterPath path;

  qreal m_d = 2.0 * m_r;
  path.moveTo( 0, 0 );
  path.arcTo( -m_r, -m_r, m_d, m_d, 90, 90 );
  path.moveTo( 0, 0 );
  path.arcTo( -m_r, -m_r, m_d, m_d, 0, -90 );
  path.closeSubpath();

  return path;
}
