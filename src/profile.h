#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "feature.h"
#include "record.h"
#include "structuredtextparser.h"
#include "symbol.h"

class Profile: public Symbol {
public:
  Profile(QString path);
  virtual ~Profile();

  virtual QPainterPath painterPath(void);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

  qreal x_datum(void);
  qreal y_datum(void);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  Features* m_profile;
  QRectF m_activeRect;
  qreal m_x_datum, m_y_datum;
  qreal m_x_origin, m_y_origin;
};

#endif /* __PROFILE_H__ */
