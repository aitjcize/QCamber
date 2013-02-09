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

  painterPath();
}

QPainterPath DonutRSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  m_cachedPath.addEllipse(-m_od / 2, -m_od / 2, m_od, m_od);
  m_cachedPath.addEllipse(-m_id / 2, -m_id / 2, m_id, m_id);

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
