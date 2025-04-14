/**
 * @file   symbol.cpp
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

#include "symbol.h"

#include <QDebug>

#include "context.h"
#include "odbppgraphicsscene.h"
#include "graphicslayerscene.h"

Symbol::Symbol(QString name, QString pattern, Polarity polarity,
    AttribData attr):
  m_name(name), m_pattern('^' + pattern + '$'), m_pen(QPen(Qt::red, 0)), m_brush(Qt::red),
  m_polarity(polarity), m_selected(false), m_attrib(attr)
{
  setHandlesChildEvents(false);

  // Since Layer will redraw all symbol visible everytime, using cache
  // will slow down the performance
  setCacheMode(NoCache);
}

Symbol::~Symbol()
{
  /*
  for (int i = 0; i < m_symbols.size(); ++i) {
    delete m_symbols[i];
  }
  */
}

QString Symbol::name(void)
{
  return m_name;
}

QString Symbol::infoText(void)
{
  QString info = QString("Pad, X=%1, Y=%2, %3, %4") \
    .arg(pos().x()).arg(pos().y()) \
    .arg(m_name).arg((m_polarity == P)? "POS": "NEG");

  info += QString(", Ang=%1").arg(rotation());
  if (transform().m11() == -1) {
    info += ", Mirror";
  }

  return info;
}

QString Symbol::longInfoText(void)
{
  QString result(
      "Pad\n\n"
      "X\t= %1\n"
      "Y\t= %2\n"
      "Symbol\t= %3\n"
      "Polarity\t= %4\n"
      "Angle\t= %5\n"
      "Mirror\t= %6\n"
  );
  return result.arg(pos().x()).arg(pos().y()) \
    .arg(m_name).arg((m_polarity == P)? "POS": "NEG").arg(rotation()) \
    .arg(transform().m11() == -1? "Yes": "No");
}

AttribData Symbol::attrib(void)
{
  return m_attrib;
}

QRectF Symbol::boundingRect() const
{
  if (m_symbols.count()) {
    return childrenBoundingRect();
  } else {
    return m_bounding;
  }
}

void Symbol::setPen(const QPen& pen)
{
  m_pen = pen;

  for (QList<Symbol*>::iterator it = m_symbols.begin();
      it != m_symbols.end(); ++it) {
    (*it)->setPen(pen);
  }
}

void Symbol::setBrush(const QBrush& brush)
{
  m_brush = brush;

  for (QList<Symbol*>::iterator it = m_symbols.begin();
      it != m_symbols.end(); ++it) {
    (*it)->setBrush(brush);
  }
}

void Symbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
      QWidget *)
{
  // Paint painterPath
  if (m_polarity == P) {
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
  } else {
    if (m_selected) {
      painter->setPen(m_pen);
      painter->setBrush(m_brush);
    } else {
      painter->setPen(QPen(ctx.bg_color, 0));
      painter->setBrush(ctx.bg_color);
    }
  }

  painter->drawPath(painterPath());
}

QPainterPath Symbol::painterPath(void)
{
  m_bounding = QRectF();
  return QPainterPath();
}

void Symbol::addChild(Symbol* symbol)
{
  symbol->setParentItem(this);
  m_symbols.append(symbol);
}

void Symbol::restoreColor(void)
{
  m_selected = false;
  setPen(m_prevPen);
  setBrush(m_prevBrush);
  update();
}

void Symbol::mousePressEvent(QGraphicsSceneMouseEvent* )
{
  GraphicsLayerScene* s = dynamic_cast<GraphicsLayerScene*>(scene());

  if (!s || !s->highlight() || m_selected) {
    return;
  }

  m_selected = true;
  m_prevPen = m_pen;
  m_prevBrush = m_brush;

  setPen(QPen(Qt::blue, 0));
  setBrush(Qt::blue);
  update();

  s->updateSelection(this);
}

void Symbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* )
{
}
