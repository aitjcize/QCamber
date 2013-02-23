#include "rectanglesymbol.h"

#include <QtGui>
#include <QRegExp>


RectangleSymbol::RectangleSymbol(QString def, Polarity polarity):
    Symbol(def, "rect([0-9.]+)x([0-9.]+)(?:(x[cr])([0-9.]+)(?:x([1-4]+))?)?", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  if (caps[3] == "xr") {
    m_rad = caps[4].toDouble() / 1000.0;
    m_type = ROUNDED;
  } else if (caps[3] == "xc") {
    m_rad = caps[4].toDouble() / 1000.0;
    m_type = CHAMFERED;
  } else {  
    m_rad = 0;
    m_type = NORMAL;
  }
  if (caps[5].length()) {
    m_corners = 0;
    QByteArray cors = caps[5].toAscii();
    for (int i = 0; i < cors.count(); ++i) {
      m_corners |= (1 << (cors[i] - '1'));
    }
  } else {
    m_corners = 15;
  }

  painterPath();
}

QPainterPath RectangleSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  QRectF rect(-m_w / 2, -m_h / 2, m_w, m_h);
  QRectF r = rect.normalized();

  if (r.isNull())
    return m_cachedPath;

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();

  if (m_type == NORMAL || m_rad <= 0) {
    m_cachedPath.addRect(x, y, w, h);
    goto ret;
  }

  m_rad = qMin(qMin(w / 2, h / 2), m_rad);

  if (m_corners & 2) {
    if (m_type == ROUNDED) {
      m_cachedPath.arcMoveTo(x, y, m_rad, m_rad, 180);
      m_cachedPath.arcTo(x, y, m_rad, m_rad, 180, -90);
    } else {
      m_cachedPath.moveTo(x, y+m_rad);
      m_cachedPath.lineTo(x+m_rad, y);
      m_cachedPath.lineTo(x+w-m_rad, y);
    }
  } else {
    m_cachedPath.moveTo(x, y);
    m_cachedPath.lineTo(x+w-m_rad, y);
  }

  if (m_corners & 1) {
    if (m_type == ROUNDED) {
      m_cachedPath.arcTo(x+w-m_rad, y, m_rad, m_rad, 90, -90);
    } else {
      m_cachedPath.lineTo(x+w, y+m_rad);
      m_cachedPath.lineTo(x+w, y+h-m_rad);
    }
  } else {
    m_cachedPath.lineTo(x+w, y);
    m_cachedPath.lineTo(x+w, y+h-m_rad);
  }

  if (m_corners & 8) {
    if (m_type == ROUNDED) {
      m_cachedPath.arcTo(x+w-m_rad, y+h-m_rad, m_rad, m_rad, 0, -90);
    } else {
      m_cachedPath.lineTo(x+w-m_rad, y+h);
      m_cachedPath.lineTo(x+m_rad, y+h);
    }
  } else {
    m_cachedPath.lineTo(x+w, y+h);
    m_cachedPath.lineTo(x+m_rad, y+h);
  }

  if (m_corners & 4) {
    if (m_type == ROUNDED) {
      m_cachedPath.arcTo(x, y+h-m_rad, m_rad, m_rad, 270, -90);
    } else {
      m_cachedPath.lineTo(x, y+h-m_rad);
    }
  } else {
    m_cachedPath.lineTo(x, y+h);
  }
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
