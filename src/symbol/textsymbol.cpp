#include "textsymbol.h"

#include <QtGui>
#include <QMatrix>

#include "fontparser.h"
#include "context.h"

TextSymbol::TextSymbol(TextRecord* rec): Symbol("text", "text")
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

  painterPath();
}

QPainterPath TextSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  m_cachedPath.setFillRule(Qt::WindingFill);

  FontParser parser(ctx.loader->absPath("fonts/" + m_font));
  FontDataStore* data = parser.parse(); 

  QMatrix mat(m_xsize / data->xsize(), 0, 0, m_ysize / data->ysize(), 0, 0);

  for (int i = 0; i < m_text.length(); ++i) {
    CharRecord* rec = data->charRecord(m_text[i].toAscii());
    if (rec) {
      QPainterPath path = mat.map(rec->painterPath(m_width_factor));
      m_cachedPath.addPath(path);
    }
    mat.translate(data->xsize() + data->offset(), 0);
  }

  QRectF b = m_cachedPath.boundingRect();
  QMatrix mat2;
  mat2.translate(-b.x(), -(b.y() + b.height()));
  m_cachedPath = mat2.map(m_cachedPath);

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
