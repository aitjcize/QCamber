#include "ellipsesymbol.h"

#include <QtGui>
#include <QRegExp>


EllipseSymbol::EllipseSymbol(QString def, Polarity polarity):
    Symbol("el", "el([0-9.]+)x([0-9.]+)", polarity), m_def(def)
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
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  m_cachedPath.addEllipse(-m_w / 2, -m_h / 2, m_w, m_h);

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
