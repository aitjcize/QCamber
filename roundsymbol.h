#ifndef __ROUNDSYMBOL_H__
#define __ROUNDSYMBOL_H__

#include "symbol.h"

class RoundSymbol: public Symbol {
public:

  RoundSymbol(Params params);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:

private:
  int m_d;
};

#endif /* __ROUNDSYMBOL_H__ */
