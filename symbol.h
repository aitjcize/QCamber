#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <QMap>
#include <QString>
#include <QGraphicsItem>

class Symbol: public QGraphicsItem {
public:
  Symbol(QString name, QString pattern);

  QString name(void);

  QRectF boundingRect() const = 0;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget) = 0;

protected:
  QString m_name;
  QString m_pattern;
};

#endif /* __SYMBOL_H__ */
