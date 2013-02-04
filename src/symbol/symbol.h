#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdexcept>

#include <QMap>
#include <QString>
#include <QGraphicsItem>
#include <QPainterPath>

class InvalidSymbolException: public std::exception {
public:
  InvalidSymbolException(const char* msg): m_msg(msg) {}
  virtual const char* what() const throw() { return m_msg; }

private:
  const char* m_msg;
};

class Symbol: public QGraphicsItem {
public:
  Symbol(QString name, QString pattern);

  QString name(void);

  virtual QRectF boundingRect() const = 0;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget) = 0;
  virtual void addShape(QPainterPath& path) = 0;

protected:
  QString m_name;
  QString m_pattern;
};

#endif /* __SYMBOL_H__ */
