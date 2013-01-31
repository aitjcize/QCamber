#include "donutsymbol.h"

#include <QtGui>

DonutSymbol::DonutSymbol(Params params): Symbol("donut_r", params)
{
  m_od = params["od"].toDouble();
  m_id = params["id"].toDouble();
}

QRectF DonutSymbol::boundingRect() const
{
  return QRectF(-m_od / 2, -m_od / 2, m_od, m_od);
}

void DonutSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  qreal rad = (m_od + m_id) / 4;
  qreal pen_width = (m_od - m_id) / 2;
  painter->setPen(QPen(Qt::red, pen_width));
  painter->drawEllipse(-rad, -rad, rad * 2, rad * 2);
}
