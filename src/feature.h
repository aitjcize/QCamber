#ifndef __FEATURES_H__
#define __FEATURES_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "symbol.h"
#include "record.h"
#include "featuresparser.h"
#include "layergraphicseffect.h"

class Features: public Symbol {
public:
  Features(QString path);
  ~Features();

  void setOpacity(qreal opacity);
  void setDoComposite(bool status);

private:
  FeaturesDataStore* m_ds;
  QList<Symbol*> m_symbols;

  LayerGraphicsEffect* m_layerEffect;
};

#endif /* __FEATURES_H__ */
