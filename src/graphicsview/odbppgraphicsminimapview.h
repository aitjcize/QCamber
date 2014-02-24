/**
 * @file   odbppgraphicsminimapview.h
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

#ifndef __ODBPPGRAPHICSMINIMAPVIEW_H__
#define __ODBPPGRAPHICSMINIMAPVIEW_H__

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "layer.h"
#include "odbppgraphicsscene.h"
#include "profile.h"

class ODBPPGraphicsMiniMapView: public QGraphicsView {
  Q_OBJECT

public:
  ODBPPGraphicsMiniMapView(QWidget* parent = 0);
  ~ODBPPGraphicsMiniMapView();

  void loadProfile(QString step);
  void zoomToAll(void);
  void scaleView(qreal scaleFactor);

signals:
  void minimapRectSelected(QRectF rect);

public slots:
  void zoomToRect(QRectF rect);
  void zoomMainViewToRect(QRectF rect);
  void redrawSceneRect(QRectF rect);
  void setBackgroundColor(QColor color);
  void updateLayerViewport(void);

protected:
  virtual void keyPressEvent(QKeyEvent* event);
  virtual void wheelEvent(QWheelEvent* event);
  virtual void resizeEvent(QResizeEvent* event);

private:
  ODBPPGraphicsScene* m_scene;
  QGraphicsRectItem* m_rect;
  Profile* m_profile;
};

#endif /* __ODBPPGRAPHICSMINIMAPVIEW_H__ */
