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

  m_bounding = painterPath().boundingRect();
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
  QPainterPath path = painterPath();

  if (m_brec->bg) {
    painter->setPen(QPen(ctx.bg_color, 0));
    painter->setBrush(ctx.bg_color);

    QRectF b = path.boundingRect();
    const qreal offset = 0.1;
    b.setX(b.x() - offset);
    b.setWidth(b.width() + offset * 2);
    painter->drawRect(b);
  }

  painter->setPen(m_pen);
  painter->setBrush(m_brush);
  painter->drawPath(path);
}

QPainterPath BarcodeSymbol::painterPath(void)
{
  QPainterPath path;

  QString bar_pattern = Code39::encode(m_brec->text, m_brec->cs, m_brec->fasc);

  qreal offset = 0;
  qreal narrow = m_brec->w;
  qreal wide = narrow * 3;

  for (int i = 0; i < bar_pattern.length(); ++i) {
    switch (bar_pattern[i].toAscii()) {
      case 'W':
        path.addRect(offset, 0, wide, -m_brec->h);
        offset += wide;
        break;
      case 'N':
        path.addRect(offset, 0, narrow, -m_brec->h);
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
    QPainterPath p = TextSymbol::painterPath();
    // restore orientation
    m_brec->orient = orient_bak;
    QRectF tb = p.boundingRect();
    QRectF bb = path.boundingRect();
    qreal ox = (bb.width() - tb.width()) / 2.0;

    if (m_brec->astr_pos == BarcodeRecord::T) {
      p.translate(ox, -m_brec->h -0.03);
    } else {
      p.translate(ox, tb.height() + 0.03);
    }
    path.addPath(p);
  }
  path.setFillRule(Qt::WindingFill);

  return path;
}
