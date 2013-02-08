#include "charsymbol.h"

#include <QtGui>

CharSymbol::CharSymbol(CharRecord* rec): Symbol("char", "char")
{
  m_tchar = rec->tchar;
  m_lines = rec->lines;

  painterPath();
}

QPainterPath CharSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();
  m_valid = true;

  m_cachedPath.setFillRule(Qt::WindingFill);

  for (QList<CharLineRecord*>::iterator it = m_lines.begin();
      it != m_lines.end(); ++it) {
    CharLineRecord* rec = (*it);
    m_cachedPath.addPath(rec->painterPath());
  }

  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();

  return m_cachedPath;
}
