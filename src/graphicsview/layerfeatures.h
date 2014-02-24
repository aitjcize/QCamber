/**
 * @file   layerfeatures.h
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

#ifndef __LAYERFEATURES_H__
#define __LAYERFEATURES_H__

#include <QGraphicsScene>
#include <QGridLayout>
#include <QList>
#include <QMap>
#include <QStandardItemModel>
#include <QString>
#include <QTextEdit>

#include "featuresparser.h"
#include "macros.h"
#include "record.h"
#include "symbol.h"

class LayerFeatures: public Symbol {
public:
  LayerFeatures(QString step, QString path, bool stepRepeat = false);
  virtual ~LayerFeatures();

  virtual QRectF boundingRect() const;
  void addToScene(QGraphicsScene* scene);

  qreal x_datum(void) { return m_x_datum; }
  qreal y_datum(void) { return m_y_datum; }
  FeaturesDataStore* dataStore(void) { return m_ds; }

  QStandardItemModel* reportModel(void);

  void setTransform(const QTransform& matrix, bool combine = false);
  void setPos(QPointF pos);
  void setPos(qreal x, qreal y);
  void setVisible(bool status);
  void setShowStepRepeat(bool status);

protected:
  void loadStepAndRepeat(void);

private:
  LayerFeatures* m_virtualParent;
  QString m_step;
  QString m_path;
  FeaturesDataStore* m_ds;
  QGraphicsScene* m_scene;
  QRectF m_activeRect;
  qreal m_x_datum, m_y_datum;
  qreal m_x_origin, m_y_origin;
  bool m_stepRepeatLoaded;
  bool m_showStepRepeat;
  QList<Symbol*> m_symbols;
  QList<LayerFeatures*> m_repeats;
  QStandardItemModel* m_reportModel;

  FeaturesDataStore::CountMapType m_posLineCount;
  FeaturesDataStore::CountMapType m_negLineCount;
  FeaturesDataStore::CountMapType m_posPadCount;
  FeaturesDataStore::CountMapType m_negPadCount;
  FeaturesDataStore::CountMapType m_posArcCount;
  FeaturesDataStore::CountMapType m_negArcCount;
  unsigned m_posSurfaceCount;
  unsigned m_negSurfaceCount;
  unsigned m_posTextCount;
  unsigned m_negTextCount;
  unsigned m_posBarcodeCount;
  unsigned m_negBarcodeCount;
};

#endif /* __LAYERFEATURES_H__ */
