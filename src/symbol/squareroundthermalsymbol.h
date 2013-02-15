#ifndef __SQUAREROUNDTHERMALSYMBOL_H__
#define __SQUAREROUNDTHERMALSYMBOL_H__

#include "symbol.h"

class SquareRoundThermalSymbol: public Symbol {
public:

  SquareRoundThermalSymbol(QString def, Polarity polarity);

  virtual QPainterPath painterPath(void);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

protected:

private:
  QString m_def;
  qreal m_od;
  qreal m_id;
  qreal m_angle;
  int m_num_spokes;
  qreal m_gap;
  QPainterPath m_sub;
};

#endif /* __SQUAREROUNDTHERMALSYMBOL_H__ */
