#ifndef __TRIANGLESYMBOL_H__
#define __TRIANGLESYMBOL_H__

#include "symbol.h"

class TriangleSymbol: public Symbol {
public:

  TriangleSymbol(QString def);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_base;
  qreal m_h;
};

#endif /* __TRIANGLESYMBOL_H__ */
