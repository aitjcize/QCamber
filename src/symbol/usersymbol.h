#ifndef __USERSYMBOL_H__
#define __USERSYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class UserSymbol: public Symbol {
public:

  UserSymbol(QString def);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);
  QPainterPath painterPath(void);

private:
  QString m_def;
  qreal m_d;
  QRectF bounding;
  FeaturesDataStore* m_ds;
  QList<Record*> m_records;
};

#endif /* __USERSYMBOL_H__ */
