/**
 * @file   notesymbol.cpp
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

#include "notesymbol.h"

#include <QtWidgets>


NoteSymbol::NoteSymbol(const NoteRecord* rec): Symbol("note")
{
  setFlag(ItemIgnoresTransformations);

  m_timestamp = rec->timestamp;
  m_user = rec->user;
  m_x = rec->x;
  m_y = rec->y;
  m_text = rec->text;

  QDateTime t = QDateTime::fromSecsSinceEpoch(m_timestamp);
  QString noteTmpl("Time: %1\nUser: %2\nNote: %3");
  setToolTip(noteTmpl.arg(t.toString(), m_user, m_text));

  m_bounding = painterPath().boundingRect();
}

QPainterPath NoteSymbol::painterPath(void)
{
  QPainterPath path;

  qreal side = 15;
  qreal hside = side / 2;

  path.lineTo(hside, 0);
  path.lineTo(side, -hside);
  path.lineTo(hside, -hside);
  path.lineTo(hside, -side);
  path.lineTo(0, -hside);
  path.closeSubpath();

  return path;
}

void NoteSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setPen(QPen(Qt::white, 0));
  painter->setBrush(Qt::gray);
  painter->drawPath(painterPath());
}

void NoteSymbol::mousePressEvent(QGraphicsSceneMouseEvent* )
{
}

void NoteSymbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* )
{
}
