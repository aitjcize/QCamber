#ifndef __NOTESYMBOL_H__
#define __NOTESYMBOL_H__

#include "record.h"
#include "symbol.h"

class NoteSymbol: public Symbol {
public:
  NoteSymbol(const NoteRecord* rec);

  QPainterPath painterPath(void);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  QString m_def;
  qreal m_r;

  int m_timestamp;
  QString m_user;
  qreal m_x, m_y;
  QString m_text;
};

#endif /* __NOTESYMBOL_H__ */
