/**
 * @file   odbppgraphicsview.cpp
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

#include "odbppgraphicsview.h"

#include "context.h"
#include "graphicslayer.h"
#include "symbolfactory.h"

#include <QScrollBar>

ODBPPGraphicsView::ODBPPGraphicsView(QWidget* parent): QGraphicsView(parent),
  m_profile(NULL)
{
  m_scene = new ODBPPGraphicsScene(this);
  m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  m_scene->setBackgroundBrush(ctx.bg_color);
  m_scene->setSceneRect(-800, -600, 1600, 1200);
  setScene(m_scene);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setCacheMode(CacheBackground);
  setOptimizationFlags(DontSavePainterState);
  setTransformationAnchor(AnchorUnderMouse);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setZoomMode(AreaZoom);

  connect(m_scene, SIGNAL(rectSelected(QRectF)), this,
      SLOT(zoomToRect(QRectF)));
  connect(horizontalScrollBar(), SIGNAL(valueChanged(int)),
      this, SLOT(updateLayerViewport()));
  connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
      this, SLOT(updateLayerViewport()));
}

ODBPPGraphicsView::~ODBPPGraphicsView()
{
  m_scene->deleteLater();
  delete m_profile;
}

void ODBPPGraphicsView::scaleView(qreal scaleFactor)
{
  scale(scaleFactor, scaleFactor);
  setTransformationAnchor(AnchorUnderMouse);
}

void ODBPPGraphicsView::scrollView(int dx, int dy)
{
  QScrollBar* hsb = horizontalScrollBar();
  hsb->setValue(hsb->value() + dx);

  QScrollBar* vsb = verticalScrollBar();
  vsb->setValue(vsb->value() + dy);
}

void ODBPPGraphicsView::setZoomMode(ZoomMode mode)
{
  m_zoomMode = mode;
  switch (mode) {
  case None:
    m_scene->setAreaZoomEnabled(false);
    setDragMode(NoDrag);
    break;
  case AreaZoom:
    m_scene->setAreaZoomEnabled(true);
    m_scene->setHighlightEnabled(false);
    setDragMode(NoDrag);
    break;
  case MousePan:
    m_scene->setAreaZoomEnabled(false);
    m_scene->setHighlightEnabled(false);
    setDragMode(ScrollHandDrag);
    break;
  }
}

void ODBPPGraphicsView::clearScene(void)
{
  m_scene->clear();
}

void ODBPPGraphicsView::addLayer(GraphicsLayer* layer)
{
  m_scene->addLayer(layer);
  updateLayerViewport();
}

void ODBPPGraphicsView::removeLayer(GraphicsLayer* layer)
{
  m_scene->removeLayer(layer);
}

void ODBPPGraphicsView::addItem(QGraphicsItem* item)
{
  m_scene->addItem(item);
}

void ODBPPGraphicsView::removeItem(QGraphicsItem* item)
{
  m_scene->removeItem(item);
}

void ODBPPGraphicsView::loadProfile(QString step)
{
  m_profile = new Profile(step);
  addLayer(m_profile);

  m_origin = new OriginSymbol();
  setBackgroundColor(ctx.bg_color);
}

void ODBPPGraphicsView::setBackgroundColor(QColor color)
{
  m_scene->setBackgroundColor(color);

  if (m_profile) {
    QColor icolor(255 - color.red(), 255 - color.green(), 255 - color.blue());
    m_origin->setPen(QPen(icolor, 0));
    m_profile->setPen(QPen(icolor, 0));
    m_profile->setBrush(Qt::transparent);
  }
}

void ODBPPGraphicsView::setMeasureEnabled(bool status)
{
  setDragMode(NoDrag);
  m_scene->setHighlightEnabled(false);
  m_scene->setMeasureEnabled(status);
}

void ODBPPGraphicsView::setHighlightEnabled(bool status)
{
  if (status) {
    setZoomMode(ODBPPGraphicsView::None);
  } else {
    setZoomMode(ODBPPGraphicsView::AreaZoom);
  }
}

void ODBPPGraphicsView::clearHighlight(void)
{
  m_scene->clearHighlight();
}

void ODBPPGraphicsView::initialZoom(void)
{
  zoomToAll();
  addItem(m_origin);
}

void ODBPPGraphicsView::zoomToAll(void)
{
  QRectF bounding(m_profile->boundingRect());
  QList<GraphicsLayer*> layers = m_scene->layers();
  for (int i = 0; i < layers.size(); ++i) {
    bounding = bounding.united(layers[i]->boundingRect());
  }
  zoomToRect(bounding);
}

void ODBPPGraphicsView::zoomToRect(QRectF rect)
{
  if (rect.isNull()) {
    return;
  }

  QRectF b = rect.normalized();
  QRectF current = transform().mapRect(QRectF(0, 0, 1, 1));
  QRectF vp = viewport()->rect();

  qreal sx = vp.width() / (current.width() * b.width() * 1.1);
  qreal sy = vp.height() / (current.height() * b.height() * 1.1);
  qreal s = qMin(sx, sy);

  scaleView(s);
  centerOn(b.center());
}

void ODBPPGraphicsView::updateLayerViewport(void)
{
  QRect vrect = viewport()->rect();
  QRectF srect = mapToScene(vrect).boundingRect();
  m_scene->updateLayerViewport(vrect, srect);

  emit sceneRectChanged(srect);
}

void ODBPPGraphicsView::wheelEvent(QWheelEvent *event)
{
  setTransformationAnchor(AnchorUnderMouse);
  scaleView(pow((double)2, -event->angleDelta().y() / 240.0));
}

void ODBPPGraphicsView::keyPressEvent(QKeyEvent* event)
{
  int offset = 500;

  if (event->modifiers() == Qt::ShiftModifier) {
    offset = 100;
  }

  switch (event->key()) {
  case Qt::Key_Home:
    zoomToAll();
    return;
  case Qt::Key_PageUp:
    setTransformationAnchor(AnchorViewCenter);
    scaleView(2);
    return;
  case Qt::Key_PageDown:
    setTransformationAnchor(AnchorViewCenter);
    scaleView(0.5);
    return;
  case Qt::Key_Up:
    scrollView(0, -offset);
    return;
  case Qt::Key_Down:
    scrollView(0, offset);
    return;
  case Qt::Key_Left:
    scrollView(-offset, 0);
    return;
  case Qt::Key_Right:
    scrollView(offset, 0);
    return;
  }
  QGraphicsView::keyPressEvent(event);
}

void ODBPPGraphicsView::resizeEvent(QResizeEvent* event)
{
  updateLayerViewport();
  QGraphicsView::resizeEvent(event);
}
