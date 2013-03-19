#include "halfovalsymbol.h"

#include <QtGui>
#include <QRegExp>

#include "macros.h"


HalfOvalSymbol::HalfOvalSymbol(const QString& def, const Polarity& polarity,
    const AttribData& attrib):
    Symbol(def, "oval_h([0-9.]+)x([0-9.]+)", polarity, attrib), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath HalfOvalSymbol::painterPath(void)
{
  QPainterPath path;

  if (m_w > m_h) {
    qreal rad = m_h / 2;
    path.moveTo(rad, -rad);
    path.arcTo(0, -m_h/2, m_h, m_h, 90, -180);
    path.lineTo(m_h - m_w, m_h/2);
    path.lineTo(m_h - m_w, -m_h/2);
    path.closeSubpath();
  } else {
    qreal rad = m_w / 2;
    path.moveTo(rad, -rad);
    path.arcTo(-m_w/2, -m_w, m_w, m_w, 0, 180);
    path.lineTo(-m_w/2, m_h - m_w);
    path.lineTo(m_w/2, m_h - m_w);
    path.closeSubpath();
  }

  return path;
}
