#ifndef __SQUAREBUTTERFLYSYMBOL_H__
#define __SQUAREBUTTERFLYSYMBOL_H__

#include "symbol.h"

class SquareButterflySymbol: public Symbol {
public:

  SquareButterflySymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_s;
};

#endif /* __SQUAREBUTTERFLYSYMBOL_H__ */
