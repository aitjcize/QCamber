/**
 * @file   odbppgraphicsscene.h
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

#ifndef __ODBPPGRAPHICSSCENE_H__
#define __ODBPPGRAPHICSSCENE_H__

#include <QGraphicsScene>
#include <QPointF>

#include "graphicslayer.h"
#include "measuregraphicsitem.h"
#include "symbol.h"

class ODBPPGraphicsScene: public QGraphicsScene {
  Q_OBJECT

public:
  typedef enum {
    S_NONE,
    S_AREA_ZOOM,
    S_AREA_ZOOM_ACTIVE,
    S_MEASURE,
    S_MEASURE_ACTIVE
  } State;

  ODBPPGraphicsScene(QObject* parent = 0);
  ~ODBPPGraphicsScene();

  void setAreaZoomEnabled(bool status);

  QList<GraphicsLayer*> layers(void);
  void addLayer(GraphicsLayer* layer);
  void removeLayer(GraphicsLayer* layer);
  void updateLayerViewport(QRect viewRect, QRectF sceneRect);

  void setMeasureEnabled(bool status);
  void setHighlightEnabled(bool status);
  void clearHighlight(void);

signals:
  void mouseMove(QPointF);
  void featureSelected(Symbol*);
  void rectSelected(QRectF);
  void measureRectSelected(QRectF);

public slots:
  void setBackgroundColor(QColor color);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);

private:
  State m_state;
  QGraphicsRectItem* m_rubberBand;
  MeasureGraphicsItem* m_measureRubberBand;
  QPointF m_rubberPS;
  QColor m_reubberBandColor;
  bool m_measured;
  QList<GraphicsLayer*> m_layers;
};

#endif /* __ODBPPGRAPHICSSCENE_H__ */
