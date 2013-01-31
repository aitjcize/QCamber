#include "odbppviewwidget.h"
#include "symbols.h"

ODBPPViewWidget::ODBPPViewWidget(QWidget* parent): QGraphicsView(parent)
{
  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-200, -200, 400, 400);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  //setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(400, 400);
  setWindowTitle(tr("test"));

  Symbol::Params params;
  params["d"] = "10";
  Symbol* symbol = new RoundSymbol(params);
  scene->addItem(symbol);
  symbol->setPos(0, 0);

  params.clear();
  params["w"] = "100";
  params["h"] = "50";
  params["xc"] = "20";
  params["corners"] = "13";
  Symbol* symbol2 = new RectangleSymbol(params);
  scene->addItem(symbol2);
  symbol->setPos(100, 0);
}
