/**
 * @file   odbppgraphicsminimapview.cpp
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

#include "odbppgraphicsminimapview.h"

#include "symbolfactory.h"
#include "context.h"

#include <QScrollBar>

ODBPPGraphicsMiniMapView::ODBPPGraphicsMiniMapView(QWidget* parent):
  QGraphicsView(parent),
  m_profile(NULL)
{
  m_scene = new ODBPPGraphicsScene(this);
  m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  m_scene->setBackgroundBrush(ctx.bg_color);
  m_scene->setSceneRect(-800, -600, 1600, 1200);
  m_scene->setAreaZoomEnabled(true);
  setScene(m_scene);
  setDragMode(NoDrag);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setCacheMode(CacheBackground);
  setOptimizationFlags(DontSavePainterState);
  setTransformationAnchor(AnchorUnderMouse);
  setViewportUpdateMode(BoundingRectViewportUpdate);

  m_rect = new QGraphicsRectItem;
  m_rect->setPen(QPen(Qt::red, 0));
  m_rect->setBrush(QColor(255, 0, 0, 128));
  m_scene->addItem(m_rect);

  connect(m_scene, SIGNAL(rectSelected(QRectF)), this,
      SLOT(zoomMainViewToRect(QRectF)));
  connect(horizontalScrollBar(), SIGNAL(valueChanged(int)),
      this, SLOT(updateLayerViewport(void)));
  connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
      this, SLOT(updateLayerViewport(void)));
}

ODBPPGraphicsMiniMapView::~ODBPPGraphicsMiniMapView()
{
  m_scene->deleteLater();
  delete m_profile;
}

void ODBPPGraphicsMiniMapView::scaleView(qreal scaleFactor)
{
  scale(scaleFactor, scaleFactor);
}

void ODBPPGraphicsMiniMapView::loadProfile(QString step)
{
  m_profile = new Profile(step);
  m_scene->addLayer(m_profile);
  updateLayerViewport();

  setBackgroundColor(ctx.bg_color);

  m_rect->setRect(m_profile->boundingRect());
}

void ODBPPGraphicsMiniMapView::setBackgroundColor(QColor color)
{
  m_scene->setBackgroundColor(color);

  if (m_profile) {
    QColor icolor(255 - color.red(), 255 - color.green(), 255 - color.blue());
    m_profile->setPen(QPen(icolor, 0));
    m_profile->setBrush(Qt::transparent);
  }
}

void ODBPPGraphicsMiniMapView::zoomToAll(void)
{
  zoomToRect(m_profile->boundingRect());
}

void ODBPPGraphicsMiniMapView::zoomToRect(QRectF rect)
{
  QRectF b = rect.normalized();
  QRectF current = transform().mapRect(QRectF(0, 0, 1, 1));
  QRectF vp = viewport()->rect();

  qreal sx = vp.width() / (current.width() * b.width() * 1.1);
  qreal sy = vp.height() / (current.height() * b.height() * 1.1);
  qreal s = qMin(sx, sy);

  scaleView(s);
  centerOn(b.center());
}

void ODBPPGraphicsMiniMapView::zoomMainViewToRect(QRectF rect)
{
  m_rect->setRect(rect);
  emit minimapRectSelected(rect);
}

void ODBPPGraphicsMiniMapView::redrawSceneRect(QRectF rect)
{
  m_rect->setRect(rect);
}

void ODBPPGraphicsMiniMapView::updateLayerViewport(void)
{
  QRect vrect = viewport()->rect();
  QRectF srect = mapToScene(vrect).boundingRect();
  m_scene->updateLayerViewport(vrect, srect);
}

void ODBPPGraphicsMiniMapView::keyPressEvent(QKeyEvent* )
{
  // Do nothing
}

void ODBPPGraphicsMiniMapView::wheelEvent(QWheelEvent* )
{
  // Do nothing
}

void ODBPPGraphicsMiniMapView::resizeEvent(QResizeEvent* event)
{
  updateLayerViewport();
  QGraphicsView::resizeEvent(event);
}
