#ifndef __DIAMONDSYMBOL_H__
#define __DIAMONDSYMBOL_H__

#include "symbol.h"

class DiamondSymbol: public Symbol {
public:

  DiamondSymbol(Params params);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:
  void addDiamond(QPainterPath& path, const QRectF& rect);

private:
  int m_w;
  int m_h;
};

#endif /* __DIAMONDSYMBOL_H__ */
