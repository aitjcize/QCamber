#ifndef __DIAMONDSYMBOL_H__
#define __DIAMONDSYMBOL_H__

#include "symbol.h"

class DiamondSymbol: public Symbol {
public:

  DiamondSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:
  void addDiamond(QPainterPath& path, const QRectF& rect);

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
};

#endif /* __DIAMONDSYMBOL_H__ */
