/**
 * @file   odbppgraphicsview.h
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

#ifndef __ODBPPGRAPHICSVIEW_H__
#define __ODBPPGRAPHICSVIEW_H__

#include <QtWidgets>
#include <QGraphicsView>
#include "graphicslayer.h"
#include "profile.h"

#include "odbppgraphicsscene.h"

class ODBPPGraphicsView: public QGraphicsView {
  Q_OBJECT

public:
  typedef enum { None = 0, AreaZoom, MousePan } ZoomMode;

  ODBPPGraphicsView(QWidget* parent = 0);
  ~ODBPPGraphicsView();

  void setZoomMode(ZoomMode mode);
  void loadProfile(QString step);
  void setMeasureEnabled(bool status);
  void setHighlightEnabled(bool status);
  void clearHighlight(void);

  void clearScene(void);
  void addLayer(GraphicsLayer* layer);
  void removeLayer(GraphicsLayer* layer);
  void addItem(QGraphicsItem* item);
  void removeItem(QGraphicsItem* item);

  void initialZoom(void);
  void zoomToAll(void);
  void scaleView(qreal scaleFactor);
  void scrollView(int dx, int dy);

signals:
  void sceneRectChanged(QRectF);

public slots:
  void zoomToRect(QRectF rect);
  void updateLayerViewport(void);
  void setBackgroundColor(QColor color);

protected:
  virtual void wheelEvent(QWheelEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);
  virtual void resizeEvent(QResizeEvent* event);

private:
  ODBPPGraphicsScene* m_scene;
  ZoomMode m_zoomMode;
  Profile* m_profile;
  Symbol* m_origin;
};

#endif /* __ODBPPGRAPHICSVIEW_H__ */
