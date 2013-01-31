#include "odbppviewwidget.h"
#include "symbols.h"

ODBPPViewWidget::ODBPPViewWidget(QWidget* parent): QGraphicsView(parent)
{
  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-400, -400, 800, 800);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  //setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setMinimumSize(600, 600);
  setWindowTitle(tr("test"));

  Symbol::Params params;
  params["d"] = "50";
  Symbol* symbol = new RoundSymbol(params);
  scene->addItem(symbol);
  symbol->setPos(0, 0);

  params.clear();
  params["w"] = "100";
  params["h"] = "50";
  params["xr"] = "20";
  params["corners"] = "13";
  Symbol* symbol2 = new RectangleSymbol(params);
  scene->addItem(symbol2);
  symbol2->setPos(100, 0);

  params.clear();
  params["w"] = "100";
  params["h"] = "50";
  Symbol* symbol3 = new OvalSymbol(params);
  scene->addItem(symbol3);
  symbol3->setPos(0, 100);

  params.clear();
  params["w"] = "100";
  params["h"] = "50";
  Symbol* symbol4 = new DiamondSymbol(params);
  scene->addItem(symbol4);
  symbol4->setPos(0, -100);

  params.clear();
  params["w"] = "60";
  params["h"] = "60";
  params["r"] = "20";
  Symbol* symbol5 = new OctagonSymbol(params);
  scene->addItem(symbol5);
  symbol5->setPos(-100, 0);

  params.clear();
  params["od"] = "60";
  params["id"] = "30";
  Symbol* symbol6 = new DonutSymbol(params);
  scene->addItem(symbol6);
  symbol6->setPos(-100, -100);

  params.clear();
  params["s"] = "40";
  Symbol* symbol7 = new SquareSymbol(params);
  scene->addItem(symbol7);
  symbol7->setPos(100, -100);
}
