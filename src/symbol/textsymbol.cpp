/**
 * @file   textsymbol.cpp
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

#include "textsymbol.h"

#include <QtGui>
#include <QMatrix>

#include "cachedparser.h"
#include "context.h"

TextSymbol::TextSymbol(const TextRecord* rec):
  Symbol("Text", "Text")
{
  if (rec == NULL) {
    return;
  }

  m_polarity = rec->polarity;
  m_x = rec->x;
  m_y = rec->y;
  m_font = rec->font;
  m_orient = rec->orient;
  m_xsize = rec->xsize;
  m_ysize = rec->ysize;
  m_width_factor = rec->width_factor;
  m_text = rec->text;
  m_version = rec->version;
  m_attrib = rec->attrib;

  m_bounding = painterPath().boundingRect();
}

QString TextSymbol::infoText(void)
{
  QString info = QString("Text, X=%1, Y=%2, %3, %4, %5") \
    .arg(m_x).arg(m_y) \
    .arg(m_text) \
    .arg((m_polarity == P)? "POS": "NEG") \
    .arg(m_font);
  return info;
}

QString TextSymbol::longInfoText(void)
{
  QString result(
      "Text\n\n"
      "X\t= %1\n"
      "Y\t= %2\n"
      "Text\t= %3\n"
      "Polarity\t= %4\n"
      "Font\t= %5\n"
  );
  return result \
    .arg(m_x).arg(m_y) \
    .arg(m_text) \
    .arg((m_polarity == P)? "POS": "NEG") \
    .arg(m_font);
}

QPainterPath TextSymbol::painterPath(void)
{
  QPainterPath path;

  path.setFillRule(Qt::WindingFill);

  QString filename = ctx.loader->absPath("fonts/" + m_font);
  FontDataStore* ds = CachedFontParser::parse(filename);

  QMatrix mat(m_xsize / ds->xsize(), 0, 0, m_ysize / ds->ysize(), 0, 0);

  for (int i = 0; i < m_text.length(); ++i) {
    CharRecord* rec = ds->charRecord(m_text[i].toLatin1());
    if (rec) {
      QPainterPath p = mat.map(rec->painterPath(m_width_factor));
      path.addPath(p);
    }
    mat.translate(ds->xsize() + ds->offset(), 0);
  }

  QRectF b = path.boundingRect();
  QMatrix mat2;
  mat2.translate(-b.x(), -(b.y() + b.height()));
  path = mat2.map(path);

  return path;
}
