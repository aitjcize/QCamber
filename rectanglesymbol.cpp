#include "rectanglesymbol.h"

#include <QtGui>

RectangleSymbol::RectangleSymbol(Params params): Symbol("rect", params)
{
  m_w = params["w"].toInt();
  m_h = params["h"].toInt();
}

QRectF RectangleSymbol::boundingRect() const
{
  return QRectF(-m_w / 2, -m_h / 2, m_w, m_h);
}

void RectangleSymbol::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  qreal rad;
  Type type;
  int corners = 0;

  if (m_params.find("xr") != m_params.end()) {
    rad = m_params["xr"].toDouble();
    type = ROUNDED;
  }
  if (m_params.find("xc") != m_params.end()) {
    rad = m_params["xc"].toDouble();
    type = CHAMFERED;
  }

  if (m_params.find("corners") == m_params.end()) {
    corners = 15;
  } else {
    QByteArray cors = m_params["corners"].toAscii();
    for (int i = 0; i < cors.count(); ++i) {
      corners |= (1 << (cors[i] - '1'));
    }
  }

  painter->setPen(QPen(Qt::red, 0));
  painter->setBrush(Qt::red);

  QPainterPath path;
  addRect(path, QRectF(-m_w / 2, -m_h / 2, m_w, m_h), ROUNDED, rad, corners);
  painter->drawPath(path);
}

void RectangleSymbol::addRect(QPainterPath& path, const QRectF& rect,
  Type type, qreal rad, int corners)
{
  QRectF r = rect.normalized();

  if (r.isNull())
    return;

  if (type == NORMAL) {
    path.addRect(r);
    return;
  }

  if (rad <= 0) {
    path.addRect(r);
    return;
  }

  qreal x = r.x();
  qreal y = r.y();
  qreal w = r.width();
  qreal h = r.height();

  rad = qMin(qMin(w / 2, h / 2), rad);

  if (corners & 2) {
    if (type == ROUNDED) {
      path.arcMoveTo(x, y, rad, rad, 180);
      path.arcTo(x, y, rad, rad, 180, -90);
    } else {
      path.moveTo(x, y+rad);
      path.lineTo(x+rad, y);
      path.lineTo(x+w-rad, y);
    }
  } else {
    path.moveTo(x, y);
    path.lineTo(x+w-rad, y);
  }

  if (corners & 1) {
    if (type == ROUNDED) {
      path.arcTo(x+w-rad, y, rad, rad, 90, -90);
    } else {
      path.lineTo(x+w, y+rad);
      path.lineTo(x+w, y+h-rad);
    }
  } else {
    path.lineTo(x+w, y);
    path.lineTo(x+w, y+h-rad);
  }

  if (corners & 8) {
    if (type == ROUNDED) {
      path.arcTo(x+w-rad, y+h-rad, rad, rad, 0, -90);
    } else {
      path.lineTo(x+w-rad, y+h);
      path.lineTo(x+rad, y+h);
    }
  } else {
    path.lineTo(x+w, y+h);
    path.lineTo(x+rad, y+h);
  }

  if (corners & 4) {
    if (type == ROUNDED) {
      path.arcTo(x, y+h-rad, rad, rad, 270, -90);
    } else {
      path.lineTo(x, y+h-rad);
    }
  } else {
    path.lineTo(x, y+h);
  }
  path.closeSubpath();
}
