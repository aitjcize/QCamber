#include "ovalsymbol.h"

#include <QtGui>

OvalSymbol::OvalSymbol(Params params): Symbol("oval", params)
{
  m_w = params["w"].toInt();
  m_h = params["h"].toInt();
}

QRectF OvalSymbol::boundingRect() const
{
  return QRectF(-m_w / 2, -m_h / 2, m_w, m_h);
}

void OvalSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  QPainterPath path;
  addOval(path, QRectF(-m_w / 2, -m_h / 2, m_w, m_h));
  painter->drawPath(path);
}

void OvalSymbol::addOval(QPainterPath& path, const QRectF& rect)
{
  QRectF r = rect.normalized();

  if (r.isNull())
    return;

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();

  qreal rad = h / 2;

  path.arcMoveTo(x, y, h, h, 90);
  path.arcTo(x, y, h, h, 270, -180);
  path.arcTo(x+w-h, y, h, h, 90, -180);
  path.lineTo(x+rad, y+h);
  path.closeSubpath();
}
