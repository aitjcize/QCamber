#ifndef __FEATURES_H__
#define __FEATURES_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "symbol.h"
#include "record.h"
#include "featuresparser.h"

class Features: public Symbol {
public:
  Features(QString path);

private:
  FeaturesDataStore* m_ds;
  QList<Record*> m_records;
  QList<Symbol*> m_symbols;
};

#endif /* __FEATURES_H__ */
