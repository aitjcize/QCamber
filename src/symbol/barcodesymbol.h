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
  QString m_barcode;
  QString m_e;
  qreal m_w, m_h;
  bool m_fasc;
  bool m_cs;
  bool m_bg;
  bool m_astr;
  BarcodeRecord::AstrPos m_astr_pos;
};

#endif /* __BARCODESYMBOL_H__ */
