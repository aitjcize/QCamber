#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdexcept>

#include <QMap>
#include <QString>
#include <QGraphicsItem>
#include <QPainter>
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

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);
  virtual QPainterPath painterPath(void) = 0;
  virtual void invalidate(void);

protected:
  QString m_name;
  QString m_pattern;
  bool m_valid;
  QRectF m_bounding;
  QPainterPath m_cachedPath;
};

#endif /* __SYMBOL_H__ */
