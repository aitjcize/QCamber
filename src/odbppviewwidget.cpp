#include "odbppviewwidget.h"
#include "symbolfactory.h"
#include "feature.h"
#include "iostream"
#include "context.h"

using namespace std;
extern Context ctx;

ODBPPViewWidget::ODBPPViewWidget(QWidget* parent): QGraphicsView(parent)
{
  scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-800, -800, 1600, 1600);
  setScene(scene);
  setCacheMode(CacheBackground);
  setDragMode(QGraphicsView::ScrollHandDrag);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  //setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(600, 600);
  setWindowTitle(tr("test"));

  /*
  Symbol* user = new UserSymbol("", P);
  scene->addItem(user);
  user->setPos(0, 0);
  */

  //Features* features = new Features("features");
  /*
  Features* profile = new Features(ctx.loader->absPath(
        "steps/pcb/profile"));
  profile->setPen(QPen(Qt::black, 0));
  profile->setBrush(Qt::white);
  scene->addItem(profile);

  Features* bot = new Features(ctx.loader->absPath(
        "steps/pcb/layers/bot/features.Z"));
  scene->addItem(bot);
  */
  scale(100, 100);
}

void ODBPPViewWidget::wheelEvent(QWheelEvent *event)
{
  scaleView(pow((double)2, -event->delta() / 240.0));
}

void ODBPPViewWidget::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

  scale(scaleFactor, scaleFactor);
}

void ODBPPViewWidget::load_feature(QString filename)
{
    Features* bot = new Features(ctx.loader->absPath(filename));
    scene->addItem(bot);
}

void ODBPPViewWidget::load_profile(QString step)
{
    QString path;
    path = "steps/" + step + "/profile";
    Features* profile = new Features(ctx.loader->absPath(path));
    profile->setPen(QPen(Qt::black, 0));
    profile->setBrush(Qt::white);
    scene->addItem(profile);

}
