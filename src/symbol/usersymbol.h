#ifndef __USERSYMBOL_H__
#define __USERSYMBOL_H__

#include "symbol.h"

#include "record.h"

class UserSymbol: public Symbol {
public:
  UserSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib);
  virtual ~UserSymbol();

private:
  QString m_def;
  qreal m_d;
};

#endif /* __USERSYMBOL_H__ */
