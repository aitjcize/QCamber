#ifndef __OCTAGONSYMBOL_H__
#define __OCTAGONSYMBOL_H__

#include "symbol.h"

class OctagonSymbol: public Symbol {
public:

  OctagonSymbol(QString def);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
      QWidget* widget);
  virtual QPainterPath painterPath(void);

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
  qreal m_r;
};

#endif /* __OCTAGONSYMBOL_H__ */
