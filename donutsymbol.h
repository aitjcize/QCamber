#ifndef __DONUTSYMBOL_H__
#define __DONUTSYMBOL_H__

#include "symbol.h"

class DonutSymbol: public Symbol {
public:

  DonutSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:

private:
  QString m_def;
  qreal m_od;
  qreal m_id;
};

#endif /* __DONUTSYMBOL_H__ */
