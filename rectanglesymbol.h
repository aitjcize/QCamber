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

  RectangleSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:
  void addRect(QPainterPath& path);

private:
  QString m_def;
  Type m_type;
  qreal m_w;
  qreal m_h;
  qreal m_rad;
  int m_corners;
};

#endif /* __RECTANGLESYMBOL_H__ */
