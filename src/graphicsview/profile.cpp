/**
 * @file   profile.cpp
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

#include "profile.h"
#include "context.h"

#include <QDebug>
#include <QTransform>

Profile::Profile(QString step, bool stepRepeat): GraphicsLayer(NULL)
{
  setHandlesChildEvents(true);

  GraphicsLayerScene* scene = new GraphicsLayerScene;
  m_features = new LayerFeatures(step, "steps/%1/profile", stepRepeat);
  m_features->addToScene(scene);
  setLayerScene(scene);
}

Profile::~Profile()
{
  delete m_features;
}

/*
void Profile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  QVector<qreal> dashes;
  dashes << 4 << 4;
  m_pen.setStyle(Qt::DashLine);
  m_pen.setDashPattern(dashes);
  m_brush = QBrush(Qt::transparent);

  Symbol::paint(painter, option, widget);
}
*/

void Profile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mousePressEvent(event);
}

void Profile::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);
}
