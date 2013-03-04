#ifndef __LINESYMBOL_H__
#define __LINESYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class LineSymbol: public Symbol {
public:
  LineSymbol(LineRecord* rec);

  virtual QString infoText(void);
  virtual QPainterPath painterPath(void);

private:
  LineRecord* m_rec;
  QString m_sym_name;
};

#endif /* __LineSymbol_H__ */
