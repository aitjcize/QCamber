#include "squaresymbol.h"

#include <QtGui>
#include <QRegExp>

SquareSymbol::SquareSymbol(QString def):
    Symbol("s", "s([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_s = caps[1].toDouble() / 1000.0;
}

QRectF SquareSymbol::boundingRect() const
{
  return QRectF(-m_s / 2, -m_s / 2, m_s, m_s);
}

void SquareSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawRect(QRectF(-m_s / 2, -m_s / 2, m_s, m_s));
}

QPainterPath SquareSymbol::painterPath(void)
{
  QPainterPath path;
  path.addRect(-m_s / 2, -m_s / 2, m_s, m_s);
  return path;
}
