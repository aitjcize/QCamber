#ifndef __SQUARESYMBOL_H__
#define __SQUARESYMBOL_H__

#include "symbol.h"

class SquareSymbol: public Symbol {
public:

  SquareSymbol(QString def);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_s;
};

#endif /* __SQUARESYMBOL_H__ */
