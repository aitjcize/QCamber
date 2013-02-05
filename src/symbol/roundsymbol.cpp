#include "roundsymbol.h"

#include <QtGui>
#include <QRegExp>

RoundSymbol::RoundSymbol(QString def):
    Symbol("r", "r([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_r = caps[1].toDouble() / 1000.0 / 2.0;
}

QRectF RoundSymbol::boundingRect() const
{
  return QRectF(-m_r, -m_r, m_r * 2, m_r * 2);
}

void RoundSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawEllipse(QPointF(0, 0), m_r, m_r);
}

QPainterPath RoundSymbol::painterPath(void)
{
  QPainterPath path;
  path.addEllipse(QPointF(0, 0), m_r, m_r);
  return path;
}
