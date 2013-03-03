#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdexcept>

#include <QBrush>
#include <QPen>
#include <QGraphicsItem>
#include <QMap>
#include <QPainter>
#include <QPainterPath>
#include <QString>

typedef enum { P = 0, N } Polarity;

class InvalidSymbolException: public std::exception {
public:
  InvalidSymbolException(const char* msg): m_msg(msg) {}
  virtual const char* what() const throw() { return m_msg; }

private:
  const char* m_msg;
};

class Symbol: public virtual QGraphicsItem {
public:
  Symbol(QString name, QString pattern = QString(), Polarity polarity=P);
  virtual ~Symbol();

  QString name(void);
  virtual QString infoText(void);

  virtual void setPen(const QPen& pen);
  virtual void setBrush(const QBrush& brush);
  virtual QPainterPath painterPath(void);
  virtual void invalidate(void);

  void addChild(Symbol* symbol);
  void restoreColor(void);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);
  virtual QPainterPath shape() const {
    return const_cast<Symbol*>(this)->painterPath();
  };

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

protected:
  QString m_name;
  QString m_pattern;
  QRectF m_bounding;
  QPen m_pen;
  QBrush m_brush;
  QPen m_prevPen;
  QBrush m_prevBrush;
  Polarity m_polarity;
  bool m_valid;
  bool m_selected;
  QList<Symbol*> m_symbols;
};

#endif /* __SYMBOL_H__ */
