#ifndef __FEATURES_H__
#define __FEATURES_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "record.h"
#include "featuresparser.h"

class Features {
public:
  Features(QString path);

  void add(QGraphicsScene* scene);

private:
  FeaturesDataStore* m_ds;
  QList<Record*> m_records;
};

#endif /* __FEATURES_H__ */
