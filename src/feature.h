#ifndef __FEATURES_H__
#define __FEATURES_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>
#include <QGridLayout>
#include <QTextEdit>

#include "symbol.h"
#include "record.h"
#include "featuresparser.h"

class Features: public Symbol {
public:
  Features(QString step, QString path);
  virtual ~Features();

  virtual QRectF boundingRect() const;
  void addToScene(QGraphicsScene* scene);
  QTableWidget *symbolCount();

  qreal x_datum(void) { return m_x_datum; }
  qreal y_datum(void) { return m_y_datum; }

  void setTransform(const QTransform & matrix, bool combine = false);
  void setPos(qreal x, qreal y);
  void setPos(QPointF pos);

private:
  Features* m_virtualParent;
  FeaturesDataStore* m_ds;
  Features* m_profile;
  QRectF m_activeRect;
  qreal m_x_datum, m_y_datum;
  qreal m_x_origin, m_y_origin;
  QList<Features*> m_repeats;
  QTransform m_trans;
};

#endif /* __FEATURES_H__ */
