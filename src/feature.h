#ifndef __FEATURES_H__
#define __FEATURES_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>
#include <QGridLayout>
#include <QTableWidget>

#include "symbol.h"
#include "record.h"
#include "featuresparser.h"

class Features: public Symbol {
public:
  Features(QString path);
  ~Features();
  QTableWidget *symbolCount();

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  FeaturesDataStore* m_ds;
};

#endif /* __FEATURES_H__ */
