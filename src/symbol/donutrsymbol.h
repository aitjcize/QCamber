#ifndef __DONUTRSYMBOL_H__
#define __DONUTRSYMBOL_H__

#include "symbol.h"

class DonutRSymbol: public Symbol {
public:

  DonutRSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:

private:
  QString m_def;
  qreal m_od;
  qreal m_id;
};

#endif /* __DONUTRSYMBOL_H__ */
