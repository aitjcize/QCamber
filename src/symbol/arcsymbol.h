#ifndef __ARCSYMBOL_H__
#define __ARCSYMBOL_H__

#include "symbol.h"
#include "record.h"

class ArcSymbol: public Symbol {
public:
  ArcSymbol(ArcRecord* rec);

  QPainterPath painterPath(void);

protected:

private:
  qreal m_xs, m_ys;
  qreal m_xe, m_ye;
  qreal m_xc, m_yc;
  int m_sym_num;
  int m_dcode;
  bool m_cw;
  QRectF m_bounding;
};

#endif /* __ARCSYMBOL_H__ */
