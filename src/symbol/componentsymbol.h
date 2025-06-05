#ifndef __COMPONENT_SYMBOL_H__
#define __COMPONENT_SYMBOL_H__

#include "symbol.h"
#include "packagedatastore.h"
#include <QPainterPath>
#include <QGraphicsSimpleTextItem>

class ComponentSymbol : public Symbol {
public:
  ComponentSymbol(const PackageDataStore::PackageInfo& info,
                  const QString& designator);
  virtual QPainterPath painterPath(void);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget);
  virtual void setPen(const QPen& pen) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
  QPainterPath m_path;
  QPointF m_pin1;
  QString m_designator;
  QFont m_designatorFont;
  QGraphicsSimpleTextItem* m_designatorItem;
};

#endif /* __COMPONENT_SYMBOL_H__ */
