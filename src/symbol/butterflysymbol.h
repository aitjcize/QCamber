#ifndef __BUTTERFLYSYMBOL_H__
#define __BUTTERFLYSYMBOL_H__

#include "symbol.h"

class ButterflySymbol: public Symbol {
public:

  ButterflySymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_r;
};

#endif /* __BUTTERFLYSYMBOL_H__ */
