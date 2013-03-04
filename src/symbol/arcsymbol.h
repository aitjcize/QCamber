#ifndef __ARCSYMBOL_H__
#define __ARCSYMBOL_H__

#include "symbol.h"
#include "record.h"

class ArcSymbol: public Symbol {
public:
  ArcSymbol(ArcRecord* rec);

  virtual QString infoText(void);
  virtual QPainterPath painterPath(void);

private:
  ArcRecord* m_rec;
  QString m_sym_name;
};

#endif /* __ARCSYMBOL_H__ */
