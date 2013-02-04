#ifndef __ROUNDSYMBOL_H__
#define __ROUNDSYMBOL_H__

#include "symbol.h"

class RoundSymbol: public Symbol {
public:

  RoundSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);
  void addShape(QPainterPath& path);

protected:

private:
  QString m_def;
  qreal m_d;
};

#endif /* __ROUNDSYMBOL_H__ */
