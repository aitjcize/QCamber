#ifndef __ELLIPSESYMBOL_H__
#define __ELLIPSESYMBOL_H__

#include "symbol.h"

class EllipseSymbol: public Symbol {
public:

  EllipseSymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
};

#endif /* __ELLIPSESYMBOL_H__ */
