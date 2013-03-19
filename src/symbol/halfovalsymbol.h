#ifndef __HALFOVALSYMBOL_H__
#define __HALFOVALSYMBOL_H__

#include "symbol.h"

class HalfOvalSymbol: public Symbol {
public:

  HalfOvalSymbol(const QString& def, const Polarity& polarity,
      const AttribData& attrib);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
};

#endif /* __HALFOVALSYMBOL_H__ */
