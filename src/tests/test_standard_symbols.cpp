#include "testviewwidget.h"

#include "testviewwidget.h"
#include "archiveloader.h"
#include "symbolfactory.h"
#include "context.h"

Context ctx;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  TestViewWidget widget;
  QGraphicsScene *scene = new QGraphicsScene();
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-400, -400, 800, 800);
  widget.setScene(scene);

  Symbol* symbol = SymbolFactory::create("r50");
  scene->addItem(symbol);
  symbol->setPos(0, 0);

  Symbol* symbol2 = SymbolFactory::create("rect100x50xr20x13");
  scene->addItem(symbol2);
  symbol2->setPos(0.1, 0);

  Symbol* symbol3 = SymbolFactory::create("oval100x50");
  scene->addItem(symbol3);
  symbol3->setPos(0, 0.1);

  Symbol* symbol4 = SymbolFactory::create("di100x50");
  scene->addItem(symbol4);
  symbol4->setPos(0, -0.1);

  Symbol* symbol5 = SymbolFactory::create("oct60x60x20");
  scene->addItem(symbol5);
  symbol5->setPos(-0.1, 0);

  Symbol* symbol6 = SymbolFactory::create("donut_r60x30");
  scene->addItem(symbol6);
  symbol6->setPos(-0.1, -0.1);

  Symbol* symbol7 = SymbolFactory::create("s40");
  scene->addItem(symbol7);
  symbol7->setPos(0.1, 0.1);
  
  widget.show();
  return app.exec();
}

