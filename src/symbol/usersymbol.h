#ifndef __USERSYMBOL_H__
#define __USERSYMBOL_H__

#include "symbol.h"

#include "featuresparser.h"
#include "record.h"

class UserSymbol: public Symbol {
public:
  UserSymbol(QString def, Polarity polarity);

private:
  QString m_def;
  qreal m_d;
  FeaturesDataStore* m_ds;
  QList<Record*> m_records;
};

#endif /* __USERSYMBOL_H__ */
