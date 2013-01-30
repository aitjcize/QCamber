#ifndef __ROUND_SYMBOL_H__
#define __ROUND_SYMBOL_H__

#include "symbol.h"

class RoundSymbol: public Symbol {
public:
  RoundSymbol(Params params);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

private:
  int m_d;
};

#endif /* __ROUND_SYMBOL_H__ */
