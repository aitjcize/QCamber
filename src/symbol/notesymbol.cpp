#include "notesymbol.h"

#include <QtGui>
#include <QRegExp>


NoteSymbol::NoteSymbol(NoteRecord* rec): Symbol("note")
{
  m_timestamp = rec->timestamp;
  m_user = rec->user;
  m_x = rec->x;
  m_y = rec->y;
  m_text = rec->text;

  QDateTime t = QDateTime::fromTime_t(m_timestamp);
  QString noteTmpl("Time: %1\nUser: %2\nNote: %3");
  setToolTip(noteTmpl.arg(t.toString(), m_user, m_text));

  painterPath();
}

QPainterPath NoteSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  qreal side = 0.04;
  qreal hside = side / 2;

  m_cachedPath.lineTo(hside, 0);
  m_cachedPath.lineTo(side, -hside);
  m_cachedPath.lineTo(hside, -hside);
  m_cachedPath.lineTo(hside, -side);
  m_cachedPath.lineTo(0, -hside);
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}

void NoteSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painterPath();
  painter->setPen(QPen(Qt::white, 0));
  painter->setBrush(Qt::gray);
  painter->drawPath(m_cachedPath);
}

void NoteSymbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  update();
}
