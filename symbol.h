#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <QMap>
#include <QString>
#include <QGraphicsItem>

class Symbol: public QGraphicsItem {
public:
  typedef QMap<QString, QString> Params;

  Symbol(QString name, Params params);
  QString name(void);

  QRectF boundingRect() const = 0;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget) = 0;

protected:
  QString m_name;
  Params m_params;
};

#endif /* __SYMBOL_H__ */
