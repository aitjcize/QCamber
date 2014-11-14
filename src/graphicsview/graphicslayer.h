/**
 * @file   graphicslayer.h
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

#ifndef __GRAPHICSLAYER_H__
#define __GRAPHICSLAYER_H__

#include <QGraphicsScene>

#include "graphicslayerscene.h"
#include "layerfeatures.h"
#include "notes.h"
#include "symbol.h"

class GraphicsLayer: public QGraphicsItem {
public:
  GraphicsLayer(QGraphicsItem* parent = 0);
  virtual ~GraphicsLayer();

  void setLayerScene(GraphicsLayerScene* scene);
  QGraphicsScene* layerScene(void);

  void setViewRect(const QRect& rect);
  void setSceneRect(const QRectF& rect);
  void setShowOutline(bool status);
  virtual void setPen(const QPen& pen);
  virtual void setBrush(const QBrush& brush);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

  void forceUpdate(void);

protected:
  GraphicsLayerScene* m_layerScene;
  QRect m_viewRect;
  QRectF m_sceneRect;
  QPixmap m_pixmap;
  QRectF m_prevSceneRect;
  QPen m_pen;
  QBrush m_brush;
  bool m_showOutline;
};

#endif /* __GRAPHICSLAYER_H__ */
