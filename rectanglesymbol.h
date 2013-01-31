#ifndef __RECTANGLESYMBOL_H__
#define __RECTANGLESYMBOL_H__

#include "symbol.h"

class RectangleSymbol: public Symbol {
public:
  typedef enum {
    NORMAL = 0,
    ROUNDED,
    CHAMFERED
  } Type;

  RectangleSymbol(Params params);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:
  void addRect(QPainterPath& path, const QRectF& rect, Type type = NORMAL,
      qreal rad = 0, int corners = 0);

private:
  int m_w;
  int m_h;
};

#endif /* __RECTANGLESYMBOL_H__ */
