#include "symbol.h"

Symbol::Symbol(QString name, Params params): m_name(name), m_params(params)
{
  
}

QString Symbol::name(void)
{
  return m_name;
}
