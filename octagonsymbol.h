#ifndef __OCTAGONSYMBOL_H__
#define __OCTAGONSYMBOL_H__

#include "symbol.h"

class OctagonSymbol: public Symbol {
public:

  OctagonSymbol(Params params);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:
  void addOctagon(QPainterPath& path, const QRectF& rect, qreal corner);

private:
  int m_w;
  int m_h;
  int m_r;
};

#endif /* __OCTAGONSYMBOL_H__ */
