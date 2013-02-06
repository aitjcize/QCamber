#include "octagonsymbol.h"

#include <QtGui>
#include <QRegExp>

OctagonSymbol::OctagonSymbol(QString def):
    Symbol("oct", "oct([0-9.]+)x([0-9.]+)x([0-9.]+)"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  m_r = caps[3].toDouble() / 1000.0;

  painterPath();
}

QPainterPath OctagonSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_valid = true;

  QRectF rect(-m_w / 2, -m_h / 2, m_w, m_h);
  QRectF r = rect.normalized();

  if (r.isNull())
    return m_cachedPath;

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();

  m_cachedPath.moveTo(x, y+h-m_r);
  m_cachedPath.lineTo(x, y+m_r);
  m_cachedPath.lineTo(x+m_r, y);
  m_cachedPath.lineTo(x+w-m_r, y);
  m_cachedPath.lineTo(x+w, y+m_r);
  m_cachedPath.lineTo(x+w, y+h-m_r);
  m_cachedPath.lineTo(x+w-m_r, y+h);
  m_cachedPath.lineTo(x+m_r, y+h);
  m_cachedPath.closeSubpath();

  m_bounding = m_cachedPath.boundingRect();
  return m_cachedPath;
}
