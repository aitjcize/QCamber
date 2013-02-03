#include "odbppviewwidget.h"
#include "symbolfactory.h"

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

  /*
  Symbol* symbol = SymbolFactory::create("r50");
  scene->addItem(symbol);
  symbol->setPos(0, 0);

  Symbol* symbol2 = SymbolFactory::create("rect100x50xr20x13");
  scene->addItem(symbol2);
  symbol2->setPos(100, 0);

  Symbol* symbol3 = SymbolFactory::create("oval100x50");
  scene->addItem(symbol3);
  symbol3->setPos(0, 100);

  Symbol* symbol4 = SymbolFactory::create("di100x50");
  scene->addItem(symbol4);
  symbol4->setPos(0, -100);

  Symbol* symbol5 = SymbolFactory::create("oct60x60x20");
  scene->addItem(symbol5);
  symbol5->setPos(-100, 0);

  Symbol* symbol6 = SymbolFactory::create("donut_r60x30");
  scene->addItem(symbol6);
  symbol6->setPos(-100, -100);

  Symbol* symbol7 = SymbolFactory::create("s40");
  scene->addItem(symbol7);
  symbol7->setPos(100, -100);
  */

  Symbol* user = new UserSymbol("construct");
  scene->addItem(user);
  user->setPos(0, 0);
  scale(1000, 1000);
}
