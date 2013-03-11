#include "profile.h"
#include "context.h"

#include <QDebug>
#include <QTransform>

Profile::Profile(QString step): GraphicsLayer(NULL)
{
  setHandlesChildEvents(true);

  GraphicsLayerScene* scene = new GraphicsLayerScene;
  m_features = new LayerFeatures(step, "steps/%1/profile");
  m_features->setShowStepRepeat(true);
  m_features->addToScene(scene);
  setLayerScene(scene);
}

Profile::~Profile()
{
  delete m_features;
}

/*
void Profile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
      QWidget *widget)
{
  QVector<qreal> dashes;
  dashes << 4 << 4;
  m_pen.setStyle(Qt::DashLine);
  m_pen.setDashPattern(dashes);
  m_brush = QBrush(Qt::transparent);

  Symbol::paint(painter, option, widget);
}
*/

void Profile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mousePressEvent(event);
}

void Profile::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  QGraphicsItem::mouseDoubleClickEvent(event);
}
