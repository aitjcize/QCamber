#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "symbol.h"
#include <QList>
#include <QString>

class ComponentsDataStore;
class QGraphicsScene;

class Components : public Symbol {
public:
  Components(QString step, QString path, bool bottomLayer = false);
  ~Components();

  void addToScene(QGraphicsScene* scene);

private:
  QList<Symbol*> m_symbols;
  bool m_bottomLayer;
};

#endif /* __COMPONENTS_H__ */
