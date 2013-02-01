#include "symbol.h"

Symbol::Symbol(QString name, QString pattern): m_name(name), m_pattern(pattern)
{
  
}

QString Symbol::name(void)
{
  return m_name;
}
