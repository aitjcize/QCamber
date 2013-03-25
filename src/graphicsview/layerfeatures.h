#ifndef __LAYERFEATURES_H__
#define __LAYERFEATURES_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>
#include <QGridLayout>
#include <QTextEdit>
#include <QStandardItemModel>

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
};

#endif /* __LAYERFEATURES_H__ */
