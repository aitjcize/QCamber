#ifndef __ORIGINSYMBOL_H__
#define __ORIGINSYMBOL_H__

#include "symbol.h"

class OriginSymbol: public Symbol {
public:
  OriginSymbol();

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);
};

#endif /* __ORIGINSYMBOL_H__ */
