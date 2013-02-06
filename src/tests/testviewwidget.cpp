#include "testviewwidget.h"
#include "context.h"

#include <cmath>

extern Context ctx;

TestViewWidget::TestViewWidget(QWidget* parent): QGraphicsView(parent)
{
  setCacheMode(CacheBackground);
  setDragMode(QGraphicsView::ScrollHandDrag);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(600, 600);
  setWindowTitle(tr("test"));

  scale(1000, 1000);
}

void TestViewWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void TestViewWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    scale(scaleFactor, scaleFactor);
}
