#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "symbol.h"
#include "record.h"
#include "structuredtextparser.h"

class Profile: public Symbol {
public:
  Profile(QString path);

  virtual QPainterPath painterPath(void);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget);

private:
  StructuredTextDataStore* m_ds;
  QRectF m_edgeBounding;
};

#endif /* __PROFILE_H__ */
