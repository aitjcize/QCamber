#ifndef __ROUNDTHERMALSQUARESYMBOL_H__
#define __ROUNDTHERMALSQUARESYMBOL_H__

#include "symbol.h"

class RoundThermalSquareSymbol: public Symbol {
public:

  RoundThermalSquareSymbol(QString def, Polarity polarity);

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

#endif /* __ROUNDTHERMALSQUARESYMBOL_H__ */
