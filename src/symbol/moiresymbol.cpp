#include "moiresymbol.h"

#include <QtGui>
#include <QRegExp>

MoireSymbol::MoireSymbol(QString def, Polarity polarity):
    Symbol("moire", "moire([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_rw = caps[1].toDouble() / 1000.0;
  m_rg = caps[2].toDouble() / 1000.0;
  m_nr = caps[3].toInt();
  m_lw = caps[4].toDouble() / 1000.0;
  m_ll = caps[5].toDouble() / 1000.0;
  m_la = caps[6].toDouble() / 1000.0;

  painterPath();
}

QPainterPath MoireSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  m_circlePath = QPainterPath();
  qreal rad = m_rw;
  m_circlePath.addEllipse(QPointF(0, 0), m_rw / 2, m_rw / 2);

  for (int i = 0; i < m_nr; ++i) {
    rad += m_rg - m_rw / 2;
    m_circlePath.addEllipse(QPointF(0, 0), rad, rad);
    rad += m_rw;
    m_circlePath.addEllipse(QPointF(0, 0), rad, rad);
  }

  qreal r = m_lw / 2;

  m_linePath = QPainterPath();
  m_linePath.setFillRule(Qt::WindingFill);

  m_linePath.addRect(-m_ll / 2, -m_lw / 2, m_ll, m_lw);
  m_linePath.addRect(-m_lw / 2, -m_ll / 2, m_lw, m_ll);
  m_linePath.addEllipse(QPointF(-m_ll / 2, 0), r, r);
  m_linePath.addEllipse(QPointF(m_ll / 2, 0), r, r);
  m_linePath.addEllipse(QPointF(0, -m_ll/2), r, r);
  m_linePath.addEllipse(QPointF(0, m_ll/2), r, r);

  m_cachedPath = m_circlePath;
  m_cachedPath.addPath(m_linePath);

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}

void MoireSymbol::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (m_polarity == P) {
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
  } else {
    painter->setPen(QPen(BG_COLOR, 0));
    painter->setBrush(BG_COLOR);
  }

  painterPath();
  painter->drawPath(m_circlePath);
  painter->drawPath(m_linePath);
}
