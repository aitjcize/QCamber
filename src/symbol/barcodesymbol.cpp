/**
 * @file   barcodesymbol.cpp
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

#include "barcodesymbol.h"

#include <QtGui>
#include <QMatrix>

#include "code39.h"
#include "context.h"
#include "fontparser.h"

BarcodeSymbol::BarcodeSymbol(const BarcodeRecord* rec):
  TextSymbol(NULL)
{
  m_polarity = rec->polarity;
  m_x = rec->x;
  m_y = rec->y;
  m_font = rec->font;
  m_orient = rec->orient;
  m_text = rec->text;
  m_xsize = 0.06;
  m_ysize = 0.06;
  m_width_factor = 3.0;

  m_barcode = rec->barcode;
  m_e = rec->e;
  m_w = rec->w;
  m_h = rec->h;
  m_fasc = rec->fasc;
  m_cs = rec->cs;
  m_bg = rec->bg;
  m_astr = rec->astr;
  m_astr_pos = rec->astr_pos;
  m_attrib = rec->attrib;

  m_bounding = painterPath().boundingRect();
}

QString BarcodeSymbol::infoText(void)
{
  QString info = QString("Text/BC, X=%1, Y=%2, %3, %4, %5, %6, %7") \
    .arg(m_x).arg(m_y) \
    .arg(m_text) \
    .arg((m_polarity == P)? "POS": "NEG") \
    .arg(m_barcode) \
    .arg(m_fasc? "full_ascii": "no_full_ascii") \
    .arg(m_cs? "cs": "no_cs");
  return info;
}

QString BarcodeSymbol::longInfoText(void)
{
  QString result(
      "Text/BC\n\n"
      "X\t= %1\n"
      "Y\t= %2\n"
      "Text\t= %3\n"
      "Polarity\t= %4\n"
      "Barcode\t= %5\n"
      "Full ASCII\t= %6\n"
      "Checksum\t= %7\n"
  );
  return result \
    .arg(m_x).arg(m_y) \
    .arg(m_text) \
    .arg((m_polarity == P)? "POS": "NEG") \
    .arg(m_barcode) \
    .arg(m_fasc? "Yes": "No") \
    .arg(m_cs? "Yes": "No");
}

void BarcodeSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem*,
    QWidget*)
{
  QPainterPath path = painterPath();

  if (m_bg) {
    painter->setPen(QPen(ctx.bg_color, 0));
    painter->setBrush(ctx.bg_color);

    QRectF b = path.boundingRect();
    const qreal offset = 0.1;
    b.setX(b.x() - offset);
    b.setWidth(b.width() + offset * 2);
    painter->drawRect(b);
  }

  painter->setPen(m_pen);
  painter->setBrush(m_brush);
  painter->drawPath(path);
}

QPainterPath BarcodeSymbol::painterPath(void)
{
  QPainterPath path;
  QString bar_pattern = Code39::encode(m_text, m_cs, m_fasc);

  qreal offset = 0;
  qreal narrow = m_w;
  qreal wide = narrow * 3;

  for (int i = 0; i < bar_pattern.length(); ++i) {
    switch (bar_pattern[i].toLatin1()) {
      case 'W':
        path.addRect(offset, 0, wide, -m_h);
        offset += wide;
        break;
      case 'N':
        path.addRect(offset, 0, narrow, -m_h);
        offset += narrow;
        break;
      case 'w':
        offset += wide;
        break;
      case 'n':
        offset += narrow;
        break;
    }
  }

  if (m_astr) {
    // Save current orientation to generate normal orientation text
    Orient orient_bak = m_orient;
    m_orient = N_0;
    QPainterPath p = TextSymbol::painterPath();
    // restore orientation
    m_orient = orient_bak;
    QRectF tb = p.boundingRect();
    QRectF bb = path.boundingRect();
    qreal ox = (bb.width() - tb.width()) / 2.0;

    if (m_astr_pos == BarcodeRecord::T) {
      p.translate(ox, -m_h -0.03);
    } else {
      p.translate(ox, tb.height() + 0.03);
    }
    path.addPath(p);
  }
  path.setFillRule(Qt::WindingFill);

  return path;
}
