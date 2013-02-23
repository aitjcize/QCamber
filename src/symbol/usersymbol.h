#ifndef __USERSYMBOL_H__
#define __USERSYMBOL_H__

#include "symbol.h"

#include "featuresparser.h"
#include "record.h"

class UserSymbol: public Symbol {
public:
  UserSymbol(QString def, Polarity polarity);
  virtual ~UserSymbol();

private:
  QString m_def;
  qreal m_d;
  FeaturesDataStore* m_ds;
};

#endif /* __USERSYMBOL_H__ */
