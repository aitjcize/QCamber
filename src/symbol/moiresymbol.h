#ifndef __MOIRESYMBOL_H__
#define __MOIRESYMBOL_H__

#include "symbol.h"

class MoireSymbol: public Symbol {
public:

  MoireSymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

protected:

private:
  QString m_def;
  qreal m_rw;
  qreal m_rg;
  int m_nr;
  qreal m_lw;
  qreal m_ll;
  qreal m_la;
  QPainterPath m_circlePath;
  QPainterPath m_linePath;
};

#endif /* __MOIRESYMBOL_H__ */
