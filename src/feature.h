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
  Features(QString path, bool single = true);
  virtual ~Features();
  void addToScene(QGraphicsScene* scene);
  QTableWidget *symbolCount();

private:
  FeaturesDataStore* m_ds;
};

#endif /* __FEATURES_H__ */
