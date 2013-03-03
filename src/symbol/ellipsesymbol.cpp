#include "ellipsesymbol.h"

#include <QtGui>
#include <QRegExp>


EllipseSymbol::EllipseSymbol(QString def, Polarity polarity):
    Symbol(def, "el([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;

  painterPath();
}

QPainterPath EllipseSymbol::painterPath(void)
{
  static bool first = true;
  QPainterPath m_cachedPath;

  m_cachedPath.addEllipse(-m_w / 2, -m_h / 2, m_w, m_h);

ret:
  if (first) {
    prepareGeometryChange();
    m_bounding = m_cachedPath.boundingRect();
    first = false;
  }

  return m_cachedPath;
}
