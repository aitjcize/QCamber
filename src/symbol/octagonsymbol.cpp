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
  QPainterPath path;
  addOctagon(path, QRectF(-m_w / 2, -m_h / 2, m_w, m_h), m_r, true);
  painter->drawPath(path);
}

void OctagonSymbol::addShape(QPainterPath& path)
{
  addOctagon(path, QRectF(-m_w / 2, -m_h / 2, m_w, m_h), m_r, false);
}

void OctagonSymbol::addOctagon(QPainterPath& path, const QRectF& rect,
    qreal c, bool offset)
{
  QRectF r = rect.normalized();
  qreal ox = 0, oy = 0;

  if (r.isNull())
    return;

  if (offset) {
    ox = pos().x();
    oy = pos().y();
  }

  qreal x = ox + r.x();
  qreal y = oy + r.y();
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
