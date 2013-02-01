#include "ovalsymbol.h"

#include <QtGui>
#include <QRegExp>

OvalSymbol::OvalSymbol(QString def):
    Symbol("oval", "oval([0-9.]+)x([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  rx.exactMatch(def);
  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble();
  m_h = caps[2].toDouble();
}

QRectF OvalSymbol::boundingRect() const
{
  return QRectF(-m_w / 2, -m_h / 2, m_w, m_h);
}

void OvalSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
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
