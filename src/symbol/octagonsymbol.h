#ifndef __OCTAGONSYMBOL_H__
#define __OCTAGONSYMBOL_H__

#include "symbol.h"

class OctagonSymbol: public Symbol {
public:

  OctagonSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);
  void addShape(QPainterPath& path);

protected:
  void addOctagon(QPainterPath& path, const QRectF& rect, qreal corner,
    bool offset);

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
  qreal m_r;
};

#endif /* __OCTAGONSYMBOL_H__ */
