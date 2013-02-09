#include "barcodesymbol.h"

#include <QtGui>
#include <QMatrix>

#include "code39.h"
#include "fontparser.h"

BarcodeSymbol::BarcodeSymbol(BarcodeRecord* rec): TextSymbol(NULL)
{
  m_x = rec->x;
  m_y = rec->y;
  m_font = rec->font;
  m_polarity = rec->polarity;
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

  painterPath();
}

#include <QDebug>

QPainterPath BarcodeSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  QString bar_pattern = Code39::encode(m_text);
  QPainterPath finalPath;

  qreal offset = 0;
  qreal narrow = m_w;
  qreal wide = narrow * 3;

  for (int i = 0; i < bar_pattern.length(); ++i) {
    switch (bar_pattern[i].toAscii()) {
      case 'W':
        finalPath.addRect(offset, 0, wide, -m_h);
        offset += wide;
        break;
      case 'N':
        finalPath.addRect(offset, 0, narrow, -m_h);
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
    QPainterPath path = TextSymbol::painterPath();
    QRectF tb = path.boundingRect();
    QRectF bb = finalPath.boundingRect();
    qreal ox = (bb.width() - tb.width()) / 2.0;

    if (m_astr_pos == BarcodeRecord::T) {
      path.translate(ox, -m_h -0.03);
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
