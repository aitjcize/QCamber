#ifndef __DONUTRSYMBOL_H__
#define __DONUTRSYMBOL_H__

#include "symbol.h"

class DonutRSymbol: public Symbol {
public:

  DonutRSymbol(const QString& def, const Polarity& polarity,
      const AttribData& attrib);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_od;
  qreal m_id;
};

#endif /* __DONUTRSYMBOL_H__ */
