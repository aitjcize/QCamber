#include "textsymbol.h"

#include <QtGui>

#include "fontparser.h"
#include "context.h"

extern Context ctx;

TextSymbol::TextSymbol(TextRecord* rec): Symbol("text", "text")
{
  m_x = rec->x;
  m_y = rec->y;
  m_font = rec->font;
  m_polarity = rec->polarity;
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
  m_valid = true;

  m_cachedPath.setFillRule(Qt::WindingFill);

  FontParser parser(ctx.loader->absPath("fonts/standard"));
  FontDataStore* data = parser.parse(); 

  for (int i = 0; i < m_text.length(); ++i) {
    Record* rec = data->charRecord(m_text[i].toAscii());
    QPainterPath path = rec->painterPath();
    path.translate(data->xsize() * i, 0);
    m_cachedPath.addPath(path);
  }

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
