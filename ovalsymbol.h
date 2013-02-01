#ifndef __OVALSYMBOL_H__
#define __OVALSYMBOL_H__

#include "symbol.h"

class OvalSymbol: public Symbol {
public:

  OvalSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:
  void addOval(QPainterPath& path, const QRectF& rect);

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
};

#endif /* __OVALSYMBOL_H__ */
