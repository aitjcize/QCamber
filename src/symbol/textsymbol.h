#ifndef __TEXTSYMBOL_H__
#define __TEXTSYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "featuresparser.h"
#include "record.h"

class TextSymbol: public Symbol {
public:
  TextSymbol(TextRecord* rec, bool isbase=false);

  virtual QString infoText(void);
  virtual QPainterPath painterPath(void);

protected:
  TextRecord* m_rec;
};

#endif /* __TEXTSYMBOL_H__ */
