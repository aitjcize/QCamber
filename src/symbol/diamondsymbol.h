#ifndef __DIAMONDSYMBOL_H__
#define __DIAMONDSYMBOL_H__

#include "symbol.h"

class DiamondSymbol: public Symbol {
public:

  DiamondSymbol(QString def);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);
  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
};

#endif /* __DIAMONDSYMBOL_H__ */
