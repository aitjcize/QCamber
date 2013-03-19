#include "notesymbol.h"

#include <QtGui>
#include <QRegExp>


NoteSymbol::NoteSymbol(const NoteRecord* rec): Symbol("note")
{
  setFlag(ItemIgnoresTransformations);

  m_timestamp = rec->timestamp;
  m_user = rec->user;
  m_x = rec->x;
  m_y = rec->y;
  m_text = rec->text;

  QDateTime t = QDateTime::fromTime_t(m_timestamp);
  QString noteTmpl("Time: %1\nUser: %2\nNote: %3");
  setToolTip(noteTmpl.arg(t.toString(), m_user, m_text));

  m_bounding = painterPath().boundingRect();
}

QPainterPath NoteSymbol::painterPath(void)
{
  QPainterPath path;

  qreal side = 15;
  qreal hside = side / 2;

  path.lineTo(hside, 0);
  path.lineTo(side, -hside);
  path.lineTo(hside, -hside);
  path.lineTo(hside, -side);
  path.lineTo(0, -hside);
  path.closeSubpath();

  return path;
}

void NoteSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(QPen(Qt::white, 0));
  painter->setBrush(Qt::gray);
  painter->drawPath(painterPath());
}

void NoteSymbol::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void NoteSymbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
}
