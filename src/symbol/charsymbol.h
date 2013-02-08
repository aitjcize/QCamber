#ifndef __CHARSYMBOL_H__
#define __CHARSYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class CharSymbol: public Symbol {
public:
  CharSymbol(CharRecord* rec);

  QPainterPath painterPath(void);

private:
  char m_tchar;
  QList<CharLineRecord*> m_lines;
};

#endif /* __CHARSYMBOL_H__ */
