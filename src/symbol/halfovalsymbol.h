#ifndef __HALFOVALSYMBOL_H__
#define __HALFOVALSYMBOL_H__

#include "symbol.h"

class HalfOvalSymbol: public Symbol {
public:

  HalfOvalSymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
};

#endif /* __HALFOVALSYMBOL_H__ */
