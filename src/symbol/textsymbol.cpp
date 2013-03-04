#include "textsymbol.h"

#include <QtGui>
#include <QMatrix>

#include "fontparser.h"
#include "context.h"

TextSymbol::TextSymbol(TextRecord* rec, bool isbase):
  Symbol("Text", "Text"), m_rec(rec)
{
  if (!isbase) {
    m_bounding = painterPath().boundingRect();
  }
}

QString TextSymbol::infoText(void)
{
  QString info = QString("Text, X=%1, Y=%2, %3, %4, %5") \
    .arg(m_rec->x).arg(m_rec->y) \
    .arg(m_rec->text) \
    .arg((m_rec->polarity == P)? "POS": "NEG") \
    .arg(m_rec->font);
  return info;
}

QPainterPath TextSymbol::painterPath(void)
{
  QPainterPath path;

  path.setFillRule(Qt::WindingFill);

  FontParser parser(ctx.loader->absPath("fonts/" + m_rec->font));
  FontDataStore* data = parser.parse(); 

  QMatrix mat(m_rec->xsize / data->xsize(), 0, 0,
      m_rec->ysize / data->ysize(), 0, 0);

  for (int i = 0; i < m_rec->text.length(); ++i) {
    CharRecord* rec = data->charRecord(m_rec->text[i].toAscii());
    if (rec) {
      QPainterPath p = mat.map(rec->painterPath(m_rec->width_factor));
      path.addPath(p);
    }
    mat.translate(data->xsize() + data->offset(), 0);
  }

  QRectF b = path.boundingRect();
  QMatrix mat2;
  mat2.translate(-b.x(), -(b.y() + b.height()));
  path = mat2.map(path);

  delete data;

  return path;
}
