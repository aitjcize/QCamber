#include "octagonsymbol.h"

#include <QtGui>
#include <QRegExp>


OctagonSymbol::OctagonSymbol(QString def, Polarity polarity):
    Symbol(def, "oct([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  m_r = caps[3].toDouble() / 1000.0;

  m_bounding = painterPath().boundingRect();
}

QPainterPath OctagonSymbol::painterPath(void)
{
  QPainterPath path;

  qreal x = -m_w / 2;
  qreal y = -m_h / 2;

  path.moveTo(x, y+m_h-m_r);
  path.lineTo(x, y+m_r);
  path.lineTo(x+m_r, y);
  path.lineTo(x+m_w-m_r, y);
  path.lineTo(x+m_w, y+m_r);
  path.lineTo(x+m_w, y+m_h-m_r);
  path.lineTo(x+m_w-m_r, y+m_h);
  path.lineTo(x+m_r, y+m_h);
  path.closeSubpath();

  return path;
}
