#ifndef __SYMBOL_POOL_H__
#define __SYMBOL_POOL_H__

#include "symbolfactory.h"
#include <QMap>

class SymbolPool {
public:
  static SymbolPool* instance();
  virtual ~SymbolPool();

  Symbol* get(const QString& def, const Polarity& polarity,
    const AttribData& attrib);

private:
  SymbolPool();

  static SymbolPool* m_instance;
  QMap<QString, Symbol*> m_cache;
};

#define SYMBOLPOOL (SymbolPool::instance())

#endif /* __SYMBOL_POOL_H__ */
