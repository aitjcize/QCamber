#ifndef __SQUARETHERMALSYMBOL_H__
#define __SQUARETHERMALSYMBOL_H__

#include "symbol.h"

class SquareThermalSymbol: public Symbol {
public:

  SquareThermalSymbol(const QString& def, const Polarity& polarity,
      const AttribData& attrib);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_od;
  qreal m_id;
  qreal m_angle;
  int m_num_spokes;
  qreal m_gap;
};

#endif /* __SQUARETHERMALSYMBOL_H__ */
