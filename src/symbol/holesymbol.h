#ifndef __HOLESYMBOL_H__
#define __HOLESYMBOL_H__

#include "symbol.h"

class HoleSymbol: public Symbol {
public:

  HoleSymbol(const QString& def, const Polarity& polarity,
      const AttribData& attrib);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_r;
  QString m_p;
  qreal m_tp;
  qreal m_tm;
};

#endif /* __HOLESYMBOL_H__ */
