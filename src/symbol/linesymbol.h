#ifndef __LINESYMBOL_H__
#define __LINESYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class LineSymbol: public Symbol {
public:
  LineSymbol(const LineRecord* rec);

  virtual QString infoText(void);
  virtual QString longInfoText(void);
  virtual QPainterPath painterPath(void);

private:
  qreal m_xs, m_ys;
  qreal m_xe, m_ye;
  int m_sym_num;
  QString m_sym_name;
  int m_dcode;
};

#endif /* __LineSymbol_H__ */
