#include "diamondsymbol.h"

#include <QtGui>
#include <QRegExp>

DiamondSymbol::DiamondSymbol(QString def):
    Symbol("di", "di([0-9.]+)x([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
}

QRectF DiamondSymbol::boundingRect() const
{
  return QRectF(-m_w / 2, -m_h / 2, m_w, m_h);
}

void DiamondSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  QPainterPath path = painterPath();
  painter->drawPath(path);
}

QPainterPath DiamondSymbol::painterPath(void)
{
  QPainterPath path;
  QRectF rect(-m_w / 2, -m_h / 2, m_w, m_h);
  QRectF r = rect.normalized();

  if (r.isNull())
    return path;

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();
  qreal wh = w / 2;
  qreal hh = h / 2;

  path.moveTo(x, y+hh);
  path.lineTo(x+wh, y);
  path.lineTo(x+w, y+hh);
  path.lineTo(x+wh, y+h);
  path.closeSubpath();
  return path;
}
