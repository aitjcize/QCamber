#ifndef __SQUARESYMBOL_H__
#define __SQUARESYMBOL_H__

#include "symbol.h"

class SquareSymbol: public Symbol {
public:

  SquareSymbol(Params params);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:

private:
  qreal m_s;
};

#endif /* __SQUARESYMBOL_H__ */
