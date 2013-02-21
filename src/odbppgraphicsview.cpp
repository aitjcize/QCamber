#include "odbppgraphicsview.h"
#include "symbolfactory.h"
#include "iostream"
#include "context.h"

using namespace std;
extern Context ctx;

ODBPPGraphicsView::ODBPPGraphicsView(QWidget* parent): QGraphicsView(parent)
{
  QGraphicsScene* scene = new ODBPPGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-800, -800, 1600, 1600);
  scene->setBackgroundBrush(BG_COLOR);

  setScene(scene);

  setCacheMode(CacheBackground);
  setDragMode(QGraphicsView::ScrollHandDrag);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  //setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(600, 600);
  setWindowTitle(tr("test"));

  scale(100, 100);
}

void ODBPPGraphicsView::wheelEvent(QWheelEvent *event)
{
  scaleView(pow((double)2, -event->delta() / 240.0));
}

void ODBPPGraphicsView::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

  scale(scaleFactor, scaleFactor);
}

Features* ODBPPGraphicsView::loadFeature(QString filename, const QColor color,
    const QBrush brush)
{
  Features* features = new Features(ctx.loader->absPath(filename));
  features->setPen(QPen(color, 0));
  features->setBrush(brush);
  scene()->addItem(features);
  return features;
}

Profile *ODBPPGraphicsView::loadProfile(QString step)
{
  QString path;
  path = QString("steps/%1/profile").arg(step.toLower());
  Profile* profile = new Profile(ctx.loader->absPath(path));

  profile->setPen(QPen(Qt::black, 0));
  profile->setBrush(Qt::transparent);
  scene()->addItem(profile);
  return profile;
}

void ODBPPGraphicsView::setBackgroundColor(QColor color)
{
  scene()->setBackgroundBrush(color);
}
