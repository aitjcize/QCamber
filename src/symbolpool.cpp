#include "symbolpool.h"

SymbolPool* SymbolPool::m_instance = NULL;

SymbolPool::SymbolPool()
{

}

SymbolPool::~SymbolPool()
{
  for (QMap<QString, Symbol*>::iterator it = m_cache.begin();
      it != m_cache.end(); ++it) {
    delete it.value();
  }
  m_instance = NULL;
}

SymbolPool* SymbolPool::instance()
{
  if (!m_instance) {
    m_instance = new SymbolPool;
  }
  return m_instance;
}

Symbol* SymbolPool::get(const QString& def, const Polarity& polarity,
    const AttribData& attrib)
{
  if (m_cache.find(def) != m_cache.end()) {
    return m_cache[def];
  }

  Symbol* symbol = SymbolFactory::create(def, polarity, attrib);

  if (symbol) {
    m_cache[def] = symbol;
  }

  return symbol;
}
