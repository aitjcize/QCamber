#include "odbppviewwidget.h"
#include "symbolfactory.h"
#include "feature.h"
#include "iostream"

using namespace std;

ODBPPViewWidget::ODBPPViewWidget(QWidget* parent): QGraphicsView(parent)
{
  QGraphicsScene *scene = new QGraphicsScene(this);
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
  Symbol* user = new UserSymbol("");
  scene->addItem(user);
  user->setPos(0, 0);
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

void ODBPPViewWidget::load_feature(QString file_name)
{
    Features features(file_name.toAscii().data());
    features.add(scene);
    //cout<<file_name.toAscii().data()<<endl;
}
