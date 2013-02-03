#ifndef __USERSYMBOL_H__
#define __USERSYMBOL_H__

#include "symbol.h"
#include <QtGui>

class UserSymbol: public Symbol {
public:

  UserSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);

protected:
  void addShape(QPainterPath& path);
  void testDraw(QPainter& painter);

private:
  QString m_def;
  qreal m_d;
  QRectF bounding;
};

#endif /* __USERSYMBOL_H__ */
