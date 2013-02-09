#include "odbppviewwidget.h"
#include "symbolfactory.h"
#include "context.h"
#include "feature.h"

extern Context ctx;

ODBPPViewWidget::ODBPPViewWidget(QWidget* parent): QGraphicsView(parent)
{
  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-400, -400, 800, 800);
  setScene(scene);
  setCacheMode(CacheBackground);
  setDragMode(QGraphicsView::ScrollHandDrag);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  //setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(600, 600);
  setWindowTitle(tr("test"));

  /*
  Symbol* user = new UserSymbol("");
  scene->addItem(user);
  user->setPos(0, 0);
  */

  Features features(ctx.loader->absPath("steps/pcb/layers/bot/features.Z"));
  //Features features("features");
  features.add(scene);

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
