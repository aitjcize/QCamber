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
  m_w = caps[1].toDouble();
  m_h = caps[2].toDouble();
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
  QPainterPath path;
  addDiamond(path, QRectF(-m_w / 2, -m_h / 2, m_w, m_h));
  painter->drawPath(path);
}

void DiamondSymbol::addDiamond(QPainterPath& path, const QRectF& rect)
{
  QRectF r = rect.normalized();

  if (r.isNull())
    return;

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
}
