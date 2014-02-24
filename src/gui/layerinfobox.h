/**
 * @file   layerinfobox.h
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

#ifndef __LAYERINFOBOX_H__
#define __LAYERINFOBOX_H__

#include <QColor>
#include <QMenu>
#include <QString>
#include <QWidget>

#include "featureshistogramwidget.h"
#include "layer.h"

namespace Ui {
class LayerInfoBox;
}

class LayerInfoBox : public QWidget
{
  Q_OBJECT

public:
  explicit LayerInfoBox(const QString& name, const QString& step,
    const QString& type);
  ~LayerInfoBox();

  QString name(void);
  QColor color(void);
  Layer* layer(void);

  void setColor(const QColor& color);
  void setLayer(Layer* layer);

  void toggle(void);
  bool isActive(void);
  void setActive(bool status);

signals:
  void toggled(bool checked);
  void activated(bool status);

public slots:
  void showContextMenu(const QPoint& point);
  void on_activeIndicator_clicked(void);
  void on_actionFeaturesHistogram_activated(void);

protected:
  virtual void mousePressEvent(QMouseEvent *ev);
    
private:
  Ui::LayerInfoBox *ui;
  QString m_name;
  QString m_step;
  QString m_type;
  QColor m_color;
  Layer* m_layer;
  bool m_checked;
  QMenu* m_contextMenu;
  FeaturesHistogramWidget m_featuresHistogramWidget;
};

#endif // __LAYERINFOBOX_H__
