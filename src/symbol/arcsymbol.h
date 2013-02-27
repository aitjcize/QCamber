#ifndef __ARCSYMBOL_H__
#define __ARCSYMBOL_H__

#include "symbol.h"
#include "record.h"

class ArcSymbol: public Symbol {
public:
  ArcSymbol(ArcRecord* rec);

  virtual QString infoText(void);
  virtual QPainterPath painterPath(void);

private:
  qreal m_xs, m_ys;
  qreal m_xe, m_ye;
  qreal m_xc, m_yc;
  int m_sym_num;
  int m_dcode;
  bool m_cw;
  QRectF m_bounding;
  QString m_sym_name;
};

#endif /* __ARCSYMBOL_H__ */
