#include "textsymbol.h"

#include <QtGui>
#include <QMatrix>

#include "fontparser.h"
#include "context.h"

TextSymbol::TextSymbol(TextRecord* rec): Symbol("Text", "Text")
{
  if (rec == NULL) {
    return;
  }

  m_polarity = rec->polarity;
  m_x = rec->x;
  m_y = rec->y;
  m_font = rec->font;
  m_orient = rec->orient;
  m_xsize = rec->xsize;
  m_ysize = rec->ysize;
  m_width_factor = rec->width_factor;
  m_text = rec->text;
  m_version = rec->version;

  m_bounding = painterPath().boundingRect();
}

QString TextSymbol::infoText(void)
{
  QString info = QString("Text, X=%1, Y=%2, %3, %4, %5") \
    .arg(m_x).arg(m_y) \
    .arg(m_text) \
    .arg((m_polarity == P)? "POS": "NEG") \
    .arg(m_font);
  return info;
}

QPainterPath TextSymbol::painterPath(void)
{
  QPainterPath path;

  path = QPainterPath();

  path.setFillRule(Qt::WindingFill);

  FontParser parser(ctx.loader->absPath("fonts/" + m_font));
  FontDataStore* data = parser.parse(); 

  QMatrix mat(m_xsize / data->xsize(), 0, 0, m_ysize / data->ysize(), 0, 0);

  for (int i = 0; i < m_text.length(); ++i) {
    CharRecord* rec = data->charRecord(m_text[i].toAscii());
    if (rec) {
      QPainterPath path = mat.map(rec->painterPath(m_width_factor));
      path.addPath(path);
    }
    mat.translate(data->xsize() + data->offset(), 0);
  }

  QRectF b = path.boundingRect();
  QMatrix mat2;
  mat2.translate(-b.x(), -(b.y() + b.height()));
  path = mat2.map(path);

  return path;
}
