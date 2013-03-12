#ifndef __MEASUREGRAPHICSITEM__
#define __MEASUREGRAPHICSITEM__

#include <QGraphicsItem>

class MeasureGraphicsItem: public QGraphicsItem {
public:
  MeasureGraphicsItem(QRectF rect = QRectF());

  virtual QRectF boundingRect() const;
  void setRect(const QRectF& rect);

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

private:
  QRectF m_rect;
};

#endif /* __MEASUREGRAPHICSITEM__ */
