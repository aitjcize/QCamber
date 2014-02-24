/**
 * @file   viewerwindow.h
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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QColor>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QSignalMapper>
#include <QVBoxLayout>

#include "context.h"
#include "featurepropertiesdialog.h"
#include "layerfeatures.h"
#include "layerinfobox.h"
#include "odbppgraphicsview.h"
#include "structuredtextparser.h"
#include "symbolcount.h"

namespace Ui {
class ViewerWindow;
}

class ViewerWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  typedef enum { U_INCH = 0, U_MM } DisplayUnit;

  explicit ViewerWindow(QWidget *parent = 0);
  ~ViewerWindow();
  void setJob(QString job);
  void setStep(QString step);
  void setLayers(const QStringList& layers, const QStringList& types);
  void clearLayout(QLayout* , bool deleteWidgets = true);
  void showLayer(QString name);
  virtual void show(void);

signals:
  void bgColorChanged(QColor);

public slots:
  void on_actionSetColor_triggered(void);

  void on_actionZoomIn_triggered(void);
  void on_actionZoomOut_triggered(void);
  void on_actionHome_triggered(void);
  void on_actionMousePan_toggled(bool checked);
  void on_actionAreaZoom_toggled(bool checked);
  void on_actionPanLeft_triggered(void);
  void on_actionPanRight_triggered(void);
  void on_actionPanUp_triggered(void);
  void on_actionPanDown_triggered(void);
  void on_actionHighlight_toggled(bool checked);
  void on_actionClearHighlight_triggered(void);
  void on_actionFeatureProperties_triggered(void);
  void on_actionMeasure_toggled(bool checked);
  void on_actionShowOutline_toggled(bool checked);
  void on_actionShowStepRepeat_toggled(bool checked);
  void on_actionShowNotes_toggled(bool checked);

protected:
  QColor nextColor(void);

private slots:
  void toggleShowLayer(bool selected);
  void layerActivated(bool status);
  void loadColorConfig();
  void unitChanged(int index);
  void updateCursorCoord(QPointF pos);
  void updateFeatureDetail(Symbol* symbol);
  void updateMeasureResult(QRectF rect);

private:
  Ui::ViewerWindow *ui;
  QString m_job;
  QString m_step;
  QList<QColor> m_colors;
  QList<LayerInfoBox*> m_visibles;
  QMap<int, bool> m_colorsMap;
  QMap<QString, LayerInfoBox*> m_SelectorMap;
  DisplayUnit m_displayUnit;
  QLabel* m_cursorCoordLabel;
  QLabel* m_featureDetailLabel;
  LayerInfoBox* m_activeInfoBox;
  bool m_transition;
  symbolcount m_symbolCountView;
  FeaturePropertiesDialog* m_featurePropertiesDialog;
};

#endif // __MAINWINDOW_H__
