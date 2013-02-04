#include "donutrsymbol.h"

#include <QtGui>
#include <QRegExp>

DonutRSymbol::DonutRSymbol(QString def):
    Symbol("donut_r", "donut_r([0-9.]+)x([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_od = caps[1].toDouble() / 1000.0;
  m_id = caps[2].toDouble() / 1000.0;
}

QRectF DonutRSymbol::boundingRect() const
{
  return QRectF(-m_od / 2, -m_od / 2, m_od, m_od);
}

void DonutRSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);

  QPainterPath path;
  addDonut(path, false);
  painter->drawPath(path);
}

void DonutRSymbol::addShape(QPainterPath& path)
{
  addDonut(path, true);
}

void DonutRSymbol::addDonut(QPainterPath& path, bool offset)
{
  path.addEllipse(-m_od / 2, -m_od / 2, m_od, m_od);
  path.addEllipse(-m_id / 2, -m_id / 2, m_id, m_id);
}
