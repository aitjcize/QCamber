#include "odbppviewwidget.h"
#include "symbol.h"
#include "roundsymbol.h"

ODBPPViewWidget::ODBPPViewWidget(QWidget* parent): QGraphicsView(parent)
{
  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-200, -200, 400, 400);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(400, 400);
  setWindowTitle(tr("test"));

  Symbol::Params params;
  params["d"] = "100";
  Symbol* symbol = new RoundSymbol(params);
  scene->addItem(symbol);
  symbol->setPos(0, 0);
}
