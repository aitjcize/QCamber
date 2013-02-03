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
  m_d = caps[1].toDouble();
}

QRectF RoundSymbol::boundingRect() const
{
  return QRectF(-m_d / 2, -m_d / 2, m_d, m_d);
}

void RoundSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);
  painter->drawEllipse(-m_d / 2, -m_d / 2, m_d, m_d);
}
