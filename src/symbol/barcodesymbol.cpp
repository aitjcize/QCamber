#include "barcodesymbol.h"

#include <QtGui>
#include <QMatrix>

#include "code39.h"
#include "context.h"
#include "fontparser.h"

BarcodeSymbol::BarcodeSymbol(BarcodeRecord* rec):
  TextSymbol(rec, true), m_brec(rec)
{
  m_brec->xsize = 0.06;
  m_brec->ysize = 0.06;
  m_brec->width_factor = 3.0;

  painterPath();
}

QString BarcodeSymbol::infoText(void)
{
  QString info = QString("Text/BC, X=%1, Y=%2, %3, %4, %5, %6, %7") \
    .arg(m_brec->x).arg(m_brec->y) \
    .arg(m_brec->text) \
    .arg((m_brec->polarity == P)? "POS": "NEG") \
    .arg(m_brec->barcode) \
    .arg(m_brec->fasc? "full_ascii": "no_full_ascii") \
    .arg(m_brec->cs? "cs": "no_cs");
  return info;
}

void BarcodeSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem*,
    QWidget*)
{
  painterPath();

  if (m_brec->bg) {
    painter->setPen(QPen(ctx.bg_color, 0));
    painter->setBrush(ctx.bg_color);

    QRectF b = m_cachedPath.boundingRect();
    const qreal offset = 0.1;
    b.setX(b.x() - offset);
    b.setWidth(b.width() + offset * 2);
    painter->drawRect(b);
  }

  painter->setPen(m_pen);
  painter->setBrush(m_brush);
  painter->drawPath(m_cachedPath);
}

QPainterPath BarcodeSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  QString bar_pattern = Code39::encode(m_brec->text, m_brec->cs, m_brec->fasc);
  QPainterPath finalPath;

  qreal offset = 0;
  qreal narrow = m_brec->w;
  qreal wide = narrow * 3;

  for (int i = 0; i < bar_pattern.length(); ++i) {
    switch (bar_pattern[i].toAscii()) {
      case 'W':
        finalPath.addRect(offset, 0, wide, -m_brec->h);
        offset += wide;
        break;
      case 'N':
        finalPath.addRect(offset, 0, narrow, -m_brec->h);
        offset += narrow;
        break;
      case 'w':
        offset += wide;
        break;
      case 'n':
        offset += narrow;
        break;
    }
  }

  if (m_brec->astr) {
    // Save current orientation to generate normal orientation text
    Orient orient_bak = m_brec->orient;
    m_brec->orient = N_0;
    QPainterPath path = TextSymbol::painterPath();
    // restore orientation
    m_brec->orient = orient_bak;
    QRectF tb = path.boundingRect();
    QRectF bb = finalPath.boundingRect();
    qreal ox = (bb.width() - tb.width()) / 2.0;

    if (m_brec->astr_pos == BarcodeRecord::T) {
      path.translate(ox, -m_brec->h -0.03);
    } else {
      path.translate(ox, tb.height() + 0.03);
    }
    finalPath.addPath(path);
  }

  m_cachedPath = finalPath;
  m_cachedPath.setFillRule(Qt::WindingFill);

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
