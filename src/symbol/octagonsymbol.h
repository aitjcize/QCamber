#ifndef __OCTAGONSYMBOL_H__
#define __OCTAGONSYMBOL_H__

#include "symbol.h"

class OctagonSymbol: public Symbol {
public:

  OctagonSymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
  qreal m_r;
};

#endif /* __OCTAGONSYMBOL_H__ */
