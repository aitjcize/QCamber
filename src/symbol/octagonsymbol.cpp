#include "octagonsymbol.h"

#include <QtGui>
#include <QRegExp>

OctagonSymbol::OctagonSymbol(QString def):
    Symbol("oct", "oct([0-9.]+)x([0-9.]+)x([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  m_r = caps[3].toDouble() / 1000.0;
}

QRectF OctagonSymbol::boundingRect() const
{
  return QRectF(-m_w / 2, -m_h / 2, m_w, m_h);
}

void OctagonSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  QPainterPath path = painterPath();
  painter->drawPath(path);
}

QPainterPath OctagonSymbol::painterPath(void)
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

  path.moveTo(x, y+h-m_r);
  path.lineTo(x, y+m_r);
  path.lineTo(x+m_r, y);
  path.lineTo(x+w-m_r, y);
  path.lineTo(x+w, y+m_r);
  path.lineTo(x+w, y+h-m_r);
  path.lineTo(x+w-m_r, y+h);
  path.lineTo(x+m_r, y+h);
  path.closeSubpath();
  return path;
}
