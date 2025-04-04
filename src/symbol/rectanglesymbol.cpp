/**
 * @file   rectanglesymbol.cpp
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

#include "rectanglesymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


RectangleSymbol::RectangleSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "rect([0-9.]+)x([0-9.]+)(?:(x[cr])([0-9.]+)(?:x([1-4]+))?)?", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toLatin1());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  if (caps[3] == "xr") {
    m_rad = caps[4].toDouble() / 1000.0;
    m_type = ROUNDED;
  } else if (caps[3] == "xc") {
    m_rad = caps[4].toDouble() / 1000.0;
    m_type = CHAMFERED;
  } else {  
    m_rad = 0;
    m_type = NORMAL;
  }
  if (caps[5].length()) {
    m_corners = 0;
    QByteArray cors = caps[5].toLatin1();
    for (int i = 0; i < cors.count(); ++i) {
      m_corners |= (1 << (cors[i] - '1'));
    }
  } else {
    m_corners = 15;
  }

  m_bounding = painterPath().boundingRect();
}

QPainterPath RectangleSymbol::painterPath(void)
{
  QPainterPath path;

  QRectF rect(-m_w / 2, -m_h / 2, m_w, m_h);
  QRectF r = rect.normalized();

  if (r.isNull())
    return path;

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();

  if (m_type == NORMAL || m_rad <= 0) {
    path.addRect(x, y, w, h);
    return path;
  }

  m_rad = qMin(qMin(w / 2, h / 2), m_rad);

  if (m_corners & 2) {
    if (m_type == ROUNDED) {
      path.arcMoveTo(x, y, m_rad, m_rad, 180);
      path.arcTo(x, y, m_rad, m_rad, 180, -90);
    } else {
      path.moveTo(x, y+m_rad);
      path.lineTo(x+m_rad, y);
      path.lineTo(x+w-m_rad, y);
    }
  } else {
    path.moveTo(x, y);
    path.lineTo(x+w-m_rad, y);
  }

  if (m_corners & 1) {
    if (m_type == ROUNDED) {
      path.arcTo(x+w-m_rad, y, m_rad, m_rad, 90, -90);
    } else {
      path.lineTo(x+w, y+m_rad);
      path.lineTo(x+w, y+h-m_rad);
    }
  } else {
    path.lineTo(x+w, y);
    path.lineTo(x+w, y+h-m_rad);
  }

  if (m_corners & 8) {
    if (m_type == ROUNDED) {
      path.arcTo(x+w-m_rad, y+h-m_rad, m_rad, m_rad, 0, -90);
    } else {
      path.lineTo(x+w-m_rad, y+h);
      path.lineTo(x+m_rad, y+h);
    }
  } else {
    path.lineTo(x+w, y+h);
    path.lineTo(x+m_rad, y+h);
  }

  if (m_corners & 4) {
    if (m_type == ROUNDED) {
      path.arcTo(x, y+h-m_rad, m_rad, m_rad, 270, -90);
    } else {
      path.lineTo(x, y+h-m_rad);
    }
  } else {
    path.lineTo(x, y+h);
  }
  path.closeSubpath();

  return path;
}
