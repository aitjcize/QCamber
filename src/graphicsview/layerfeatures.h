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
