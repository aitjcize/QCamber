#ifndef __ROUNDTHERMALROUNDSYMBOL_H__
#define __ROUNDTHERMALROUNDSYMBOL_H__

#include "symbol.h"

class RoundThermalRoundSymbol: public Symbol {
public:

  RoundThermalRoundSymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_od;
  qreal m_id;
  qreal m_angle;
  int m_num_spokes;
  qreal m_gap;
  const qreal _PI = 3.14159265;
  inline qreal radToAngle( const qreal& rad ) const{
    return ( rad * 360 / (2 * _PI) );
  }
};

#endif /* __ROUNDTHERMALROUNDSYMBOL_H__ */
