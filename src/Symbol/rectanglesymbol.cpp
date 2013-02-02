#include "rectanglesymbol.h"

#include <QtGui>
#include <QRegExp>

RectangleSymbol::RectangleSymbol(QString def):
    Symbol("rect", "rect([0-9.]+)x([0-9.]+)(?:(x[cr])([0-9.]+)(?:x([1-4]+))?)?"), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());
  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble();
  m_h = caps[2].toDouble();
  if (caps[3] == "xr") {
    m_rad = caps[4].toDouble();
    m_type = ROUNDED;
  } else if (caps[3] == "xc") {
    m_rad = caps[4].toDouble();
    m_type = CHAMFERED;
  } else {  
    m_type = NORMAL;
  }
  if (caps[5].length()) {
    m_corners = 0;
    QByteArray cors = caps[5].toAscii();
    for (int i = 0; i < cors.count(); ++i) {
      m_corners |= (1 << (cors[i] - '1'));
    }
  }
}

QRectF RectangleSymbol::boundingRect() const
{
  return QRectF(-m_w / 2, -m_h / 2, m_w, m_h);
}

void RectangleSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);

  QPainterPath path;
  addRect(path);
  painter->drawPath(path);
}

void RectangleSymbol::addRect(QPainterPath& path)
{
  QRectF rect(-m_w / 2, -m_h / 2, m_w, m_h);
  QRectF r = rect.normalized();

  if (r.isNull())
    return;

  if (m_type == NORMAL) {
    path.addRect(r);
    return;
  }

  if (m_rad <= 0) {
    path.addRect(r);
    return;
  }

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();

  m_rad = qMin(qMin(w / 2, h / 2), m_rad);

  if (m_corners & 2) {
    if (m_type == ROUNDED) {
      path.arcMoveTo(x, y, m_rad, m_rad, 180);
      path.arcTo(x, y, m_rad, m_rad, 180, -90);
    } else {
      path.moveTo(x, y+m_rad);
      path.lineTo(x+m_rad, y);
      path.lineTo(x+w-m_rad, y);
    }
  } else {
    path.moveTo(x, y);
    path.lineTo(x+w-m_rad, y);
  }

  if (m_corners & 1) {
    if (m_type == ROUNDED) {
      path.arcTo(x+w-m_rad, y, m_rad, m_rad, 90, -90);
    } else {
      path.lineTo(x+w, y+m_rad);
      path.lineTo(x+w, y+h-m_rad);
    }
  } else {
    path.lineTo(x+w, y);
    path.lineTo(x+w, y+h-m_rad);
  }

  if (m_corners & 8) {
    if (m_type == ROUNDED) {
      path.arcTo(x+w-m_rad, y+h-m_rad, m_rad, m_rad, 0, -90);
    } else {
      path.lineTo(x+w-m_rad, y+h);
      path.lineTo(x+m_rad, y+h);
    }
  } else {
    path.lineTo(x+w, y+h);
    path.lineTo(x+m_rad, y+h);
  }

  if (m_corners & 4) {
    if (m_type == ROUNDED) {
      path.arcTo(x, y+h-m_rad, m_rad, m_rad, 270, -90);
    } else {
      path.lineTo(x, y+h-m_rad);
    }
  } else {
    path.lineTo(x, y+h);
  }
  path.closeSubpath();
}
