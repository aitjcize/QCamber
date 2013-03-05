#include "ovalsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


OvalSymbol::OvalSymbol(QString def, Polarity polarity):
    Symbol(def, "oval([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath OvalSymbol::painterPath(void)
{
  QPainterPath path;

  qreal x = -m_w / 2;
  qreal y = -m_h / 2;

  if (m_w > m_h) {
    qreal rad = m_h / 2;
    path.arcMoveTo(x, y, m_h, m_h, 90);
    path.arcTo(x, y, m_h, m_h, 270, -180);
    path.arcTo(x+m_w-m_h, y, m_h, m_h, 90, -180);
    path.lineTo(x+rad, y+m_h);
    path.closeSubpath();
  } else {
    qreal rad = m_w / 2;
    path.arcMoveTo(x, y, m_w, m_w, 90);
    path.arcTo(x, y, m_w, m_w, 180, -180);
    path.arcTo(x, y+m_h-m_w, m_w, m_w, 0, -180);
    path.lineTo(x, y+rad);
    path.closeSubpath();
  }

  return path;
}
