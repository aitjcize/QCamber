/**
 * @file   graphicslayer.cpp
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

#include "graphicslayer.h"

#include <QtWidgets>

#include "context.h"
#include "odbppgraphicsscene.h"

GraphicsLayer::GraphicsLayer(QGraphicsItem* parent):
  QGraphicsItem(parent), m_showOutline(false)
{
  m_layerScene = NULL;
}

GraphicsLayer::~GraphicsLayer()
{
  if (m_layerScene) {
    delete m_layerScene;
  }
}

void GraphicsLayer::setLayerScene(GraphicsLayerScene* scene)
{
  m_layerScene = scene;
  m_layerScene->setGraphicsLayer(this);
}

QGraphicsScene* GraphicsLayer::layerScene(void)
{
  return m_layerScene;
}

void GraphicsLayer::setViewRect(const QRect& rect)
{
  m_viewRect = rect;
}

void GraphicsLayer::setSceneRect(const QRectF& rect)
{
  m_sceneRect = rect;
}

void GraphicsLayer::setShowOutline(bool status)
{
  m_showOutline = status;
  setBrush(m_brush);
  forceUpdate();
}

void GraphicsLayer::setPen(const QPen& pen)
{
  m_pen = pen;
  QList<QGraphicsItem*> items = m_layerScene->items();
  for (int i = 0; i < items.size(); ++i) {
    dynamic_cast<Symbol*>(items[i])->setPen(pen);
  }
}

void GraphicsLayer::setBrush(const QBrush& brush)
{
  QBrush tbrush = brush;
  m_brush = brush;

  if (m_showOutline) {
    tbrush = Qt::transparent;
  }

  QList<QGraphicsItem*> items = m_layerScene->items();
  for (int i = 0; i < items.size(); ++i) {
    dynamic_cast<Symbol*>(items[i])->setBrush(tbrush);
  }
}

QRectF GraphicsLayer::boundingRect() const
{
  if (m_layerScene) {
    return m_layerScene->itemsBoundingRect();
  } else {
    return QRectF();
  }
}

void GraphicsLayer::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *, QWidget *)
{
  if (!m_layerScene) {
    return;
  }

  if (m_prevSceneRect != m_sceneRect) {
    m_pixmap = QPixmap(m_viewRect.size());
    QBitmap alphaMask(m_viewRect.size());
    alphaMask.clear();
    m_pixmap.setMask(alphaMask);

    m_prevSceneRect = m_sceneRect;

    QPainter sourcePainter(&m_pixmap);
    m_layerScene->render(&sourcePainter, m_viewRect, m_sceneRect);
  }

  painter->save();
  painter->setCompositionMode(QPainter::CompositionMode_Difference);
  painter->drawPixmap(m_sceneRect, m_pixmap, m_viewRect);
  painter->restore();
}

void GraphicsLayer::forceUpdate(void)
{
  m_prevSceneRect = QRectF();
  update();
}
