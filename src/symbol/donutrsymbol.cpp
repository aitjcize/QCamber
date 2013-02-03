#include "donutrsymbol.h"

#include <QtGui>
#include <QRegExp>

DonutRSymbol::DonutRSymbol(QString def):
    Symbol("donut_r", "donut_r([0-9.]+)x([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_od = caps[1].toDouble();
  m_id = caps[2].toDouble();
}

QRectF DonutRSymbol::boundingRect() const
{
  return QRectF(-m_od / 2, -m_od / 2, m_od, m_od);
}

void DonutRSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  qreal rad = (m_od + m_id) / 4;
  qreal pen_width = (m_od - m_id) / 2;
  painter->setPen(QPen(Qt::red, pen_width));
  painter->drawEllipse(-rad, -rad, rad * 2, rad * 2);
}
