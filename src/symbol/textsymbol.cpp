#include "textsymbol.h"

#include <QtGui>
#include <QMatrix>

#include "fontparser.h"
#include "context.h"

TextSymbol::TextSymbol(TextRecord* rec, bool isbase):
  Symbol("Text", "Text"), m_rec(rec)
{
  if (!isbase) {
    painterPath();
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
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  m_cachedPath.setFillRule(Qt::WindingFill);

  FontParser parser(ctx.loader->absPath("fonts/" + m_rec->font));
  FontDataStore* data = parser.parse(); 

  QMatrix mat(m_rec->xsize / data->xsize(), 0, 0,
      m_rec->ysize / data->ysize(), 0, 0);

  for (int i = 0; i < m_rec->text.length(); ++i) {
    CharRecord* rec = data->charRecord(m_rec->text[i].toAscii());
    if (rec) {
      QPainterPath path = mat.map(rec->painterPath(m_rec->width_factor));
      m_cachedPath.addPath(path);
    }
    mat.translate(data->xsize() + data->offset(), 0);
  }

  delete data;

  QRectF b = m_cachedPath.boundingRect();
  QMatrix mat2;
  mat2.translate(-b.x(), -(b.y() + b.height()));
  m_cachedPath = mat2.map(m_cachedPath);

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
