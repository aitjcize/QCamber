#ifndef __RECTANGULARTHERMAL_H__
#define __RECTANGULARTHERMAL_H__

#include "symbol.h"

class RectangularThermal: public Symbol {
public:

  RectangularThermal(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
  qreal m_angle;
  int m_num_spokes;
  qreal m_gap;
  qreal m_air_gap;

  inline int sign(qreal val) {
    return (val >= 0) + (val < 0) * (-1);
  }
};

#endif /* __RECTANGULARTHERMAL_H__ */
