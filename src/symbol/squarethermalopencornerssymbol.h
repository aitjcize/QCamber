#ifndef __SQUARETHERMALOPENCORNERSSYMBOL_H__
#define __SQUARETHERMALOPENCORNERSSYMBOL_H__

#include "symbol.h"

class SquareThermalOpenCornersSymbol: public Symbol {
public:

  SquareThermalOpenCornersSymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_od;
  qreal m_id;
  qreal m_angle;
  int m_num_spokes;
  qreal m_gap;

  inline int sign(qreal val) {
    return (val >= 0) + (val < 0) * (-1);
  }
};

#endif /* __SQUARETHERMALOPENCORNERSSYMBOL_H__ */
