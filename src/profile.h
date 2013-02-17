#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "symbol.h"
#include "record.h"
#include "structuredtextparser.h"

class Profile: public Symbol {
public:
  Profile(QString path);

  virtual QPainterPath painterPath(void);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

  qreal x_datum(void);
  qreal y_datum(void);

private:
  StructuredTextDataStore* m_ds;
  QRectF m_activeRect;
  qreal m_x_datum, m_y_datum;
  qreal m_x_origin, m_y_origin;
};

#endif /* __PROFILE_H__ */
