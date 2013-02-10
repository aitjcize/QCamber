#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdexcept>

#include <QMap>
#include <QString>
#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>

typedef enum { P = 0, N } Polarity;

class InvalidSymbolException: public std::exception {
public:
  InvalidSymbolException(const char* msg): m_msg(msg) {}
  virtual const char* what() const throw() { return m_msg; }

private:
  const char* m_msg;
};

class Symbol: public virtual QGraphicsItemGroup {
public:
  Symbol(QString name, QString pattern, Polarity polarity=P);

  QString name(void);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);
  virtual QPainterPath painterPath(void);
  virtual void invalidate(void);

protected:
  QString m_name;
  QString m_pattern;
  QRectF m_bounding;
  QPainterPath m_cachedPath;
  Polarity m_polarity;
  bool m_valid;
};

#endif /* __SYMBOL_H__ */
