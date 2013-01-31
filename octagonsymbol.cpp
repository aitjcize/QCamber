#include "octagonsymbol.h"

#include <QtGui>

OctagonSymbol::OctagonSymbol(Params params): Symbol("di", params)
{
  m_w = params["w"].toInt();
  m_h = params["h"].toInt();
  m_r = params["r"].toInt();
}

QRectF OctagonSymbol::boundingRect() const
{
  return QRectF(-m_w / 2, -m_h / 2, m_w, m_h);
}

void OctagonSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  QPainterPath path;
  addOctagon(path, QRectF(-m_w / 2, -m_h / 2, m_w, m_h), m_r);
  painter->drawPath(path);
}

void OctagonSymbol::addOctagon(QPainterPath& path, const QRectF& rect,
    qreal c)
{
  QRectF r = rect.normalized();

  if (r.isNull())
    return;

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();

  path.moveTo(x, y+h-c);
  path.lineTo(x, y+c);
  path.lineTo(x+c, y);
  path.lineTo(x+w-c, y);
  path.lineTo(x+w, y+c);
  path.lineTo(x+w, y+h-c);
  path.lineTo(x+w-c, y+h);
  path.lineTo(x+c, y+h);
  path.closeSubpath();
}
