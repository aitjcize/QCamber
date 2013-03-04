#ifndef __BARCODESYMBOL_H__
#define __BARCODESYMBOL_H__

#include "symbol.h"

#include <QtGui>

#include "record.h"
#include "textsymbol.h"

class BarcodeSymbol: public TextSymbol {
public:
  BarcodeSymbol(BarcodeRecord* rec);

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget);
  virtual QString infoText(void);
  virtual QPainterPath painterPath(void);

private:
  BarcodeRecord* m_brec;
};

#endif /* __BARCODESYMBOL_H__ */
