#include "symbolpool.h"

SymbolPool* SymbolPool::m_Instance = NULL;

SymbolPool::SymbolPool()
{

}

SymbolPool::~SymbolPool()
{
  for (QMap<QString, Symbol*>::iterator it = m_cache.begin();
      it != m_cache.end(); ++it) {
    delete it.value();
  }
  m_Instance = NULL;
}

SymbolPool* SymbolPool::instance()
{
  if (!m_Instance) {
    m_Instance = new SymbolPool;
  }
  return m_Instance;
}

Symbol* SymbolPool::get(QString def, Polarity polarity)
{
  if (m_cache.find(def) != m_cache.end()) {
    return m_cache[def];
  }

  Symbol* symbol = SymbolFactory::create(def, polarity);

  if (symbol) {
    m_cache[def] = symbol;
  }

  return symbol;
}
