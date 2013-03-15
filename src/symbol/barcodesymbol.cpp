#include "barcodesymbol.h"

#include <QtGui>
#include <QMatrix>

#include "code39.h"
#include "context.h"
#include "fontparser.h"

BarcodeSymbol::BarcodeSymbol(BarcodeRecord* rec):
  TextSymbol(NULL)
{
  m_polarity = rec->polarity;
  m_x = rec->x;
  m_y = rec->y;
  m_font = rec->font;
  m_orient = rec->orient;
  m_text = rec->text;
  m_xsize = 0.06;
  m_ysize = 0.06;
  m_width_factor = 3.0;

  m_barcode = rec->barcode;
  m_e = rec->e;
  m_w = rec->w;
  m_h = rec->h;
  m_fasc = rec->fasc;
  m_cs = rec->cs;
  m_bg = rec->bg;
  m_astr = rec->astr;
  m_astr_pos = rec->astr_pos;

  m_bounding = painterPath().boundingRect();
}

QString BarcodeSymbol::infoText(void)
{
  QString info = QString("Text/BC, X=%1, Y=%2, %3, %4, %5, %6, %7") \
    .arg(m_x).arg(m_y) \
    .arg(m_text) \
    .arg((m_polarity == P)? "POS": "NEG") \
    .arg(m_barcode) \
    .arg(m_fasc? "full_ascii": "no_full_ascii") \
    .arg(m_cs? "cs": "no_cs");
  return info;
}

void BarcodeSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem*,
    QWidget*)
{
  QPainterPath path = painterPath();

  if (m_bg) {
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
  QString bar_pattern = Code39::encode(m_text, m_cs, m_fasc);

  qreal offset = 0;
  qreal narrow = m_w;
  qreal wide = narrow * 3;

  for (int i = 0; i < bar_pattern.length(); ++i) {
    switch (bar_pattern[i].toAscii()) {
      case 'W':
        path.addRect(offset, 0, wide, -m_h);
        offset += wide;
        break;
      case 'N':
        path.addRect(offset, 0, narrow, -m_h);
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

  if (m_astr) {
    // Save current orientation to generate normal orientation text
    Orient orient_bak = m_orient;
    m_orient = N_0;
    QPainterPath p = TextSymbol::painterPath();
    // restore orientation
    m_orient = orient_bak;
    QRectF tb = p.boundingRect();
    QRectF bb = path.boundingRect();
    qreal ox = (bb.width() - tb.width()) / 2.0;

    if (m_astr_pos == BarcodeRecord::T) {
      p.translate(ox, -m_h -0.03);
    } else {
      p.translate(ox, tb.height() + 0.03);
    }
    path.addPath(p);
  }
  path.setFillRule(Qt::WindingFill);

  return path;
}
