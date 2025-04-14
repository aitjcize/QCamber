/**
 * @file   linesymbol.cpp
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

#include "linesymbol.h"

#include <QtWidgets>

#include "featuresparser.h"
#include "symbolpool.h"

LineSymbol::LineSymbol(const LineRecord* rec):
  Symbol("Line", "Line", rec->polarity, rec->attrib)
{
  m_xs = rec->xs;
  m_ys = rec->ys;
  m_xe = rec->xe;
  m_ye = rec->ye;
  m_sym_num = rec->sym_num;
  m_sym_name = static_cast<FeaturesDataStore*>(rec->ds)->\
               symbolNameMap()[rec->sym_num];
  m_dcode = rec->dcode;

  //make sure start is at left hand side of end
  if (m_xs > m_xe) {
    qreal tmp = m_xs;
    m_xs = m_xe;
    m_xe = tmp;
    tmp = m_ys;
    m_ys = m_ye;
    m_ye = tmp;
  }

  m_bounding = painterPath().boundingRect();
}

QString LineSymbol::infoText(void)
{
  QString info = QString("Line, XS=%1, YS=%2, XE=%3, YE=%4, %5, %6") \
    .arg(m_xs).arg(m_ys) \
    .arg(m_xe).arg(m_ye) \
    .arg(m_sym_name) \
    .arg((m_polarity == P)? "POS": "NEG");
  return info;
}

QString LineSymbol::longInfoText(void)
{
  QString result(
      "Line\n\n"
      "XS\t= %1\n"
      "YS\t= %2\n"
      "XE\t= %3\n"
      "YE\t= %4\n"
      "Symbol\t= %5\n"
      "Polarity\t= %6\n"
  );
  return result \
    .arg(m_xs).arg(m_ys) \
    .arg(m_xe).arg(m_ye) \
    .arg(m_sym_name) \
    .arg((m_polarity == P)? "POS": "NEG");
}

QPainterPath LineSymbol::painterPath()
{
  QPainterPath path;

  // Set winding fill
  path.setFillRule(Qt::WindingFill);

  Symbol *symbol = SYMBOLPOOL->get(m_sym_name, m_polarity, m_attrib);
  QPainterPath symbolPath = symbol->painterPath();
  if (symbolPath.boundingRect().height() != symbolPath.boundingRect().width()) {
    qDebug() << m_sym_name << "is not a symmetrics symbol, but we'll still "
      "try to draw lines with it";
  }

  qreal radius = (qreal)symbolPath.boundingRect().height() / 2;

  qreal sx = m_xs, sy = m_ys;
  qreal ex = m_xe, ey = m_ye;
  qreal dx = ex - sx, dy = ey - sy;
  qreal a = qAtan2(dy, dx);
  qreal rsina = radius * qSin(a), rcosa = radius * qCos(a);

  path.moveTo(sx + rsina, -(sy - rcosa));
  path.lineTo(sx - rsina, -(sy + rcosa));
  path.lineTo(ex - rsina, -(ey + rcosa));
  path.lineTo(ex + rsina, -(ey - rcosa));
  path.closeSubpath();
  path.addPath(symbolPath.translated(sx, -sy));
  path.addPath(symbolPath.translated(ex, -ey));

  return path;
}
