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

  Symbol* symbol = SymbolFactory::create("r50", P);
  scene->addItem(symbol);
  symbol->setPos(0, 0);

  Symbol* symbol2 = SymbolFactory::create("rect100x50xr20x13", P);
  scene->addItem(symbol2);
  symbol2->setPos(0.1, 0);

  Symbol* symbol3 = SymbolFactory::create("oval50x100", P);
  scene->addItem(symbol3);
  symbol3->setPos(0.2, 0);

  Symbol* symbol4 = SymbolFactory::create("di100x50", P);
  scene->addItem(symbol4);
  symbol4->setPos(0.3, 0);

  Symbol* symbol5 = SymbolFactory::create("oct60x60x20", P);
  scene->addItem(symbol5);
  symbol5->setPos(0, -0.1);

  Symbol* symbol6 = SymbolFactory::create("donut_r60x30", P);
  scene->addItem(symbol6);
  symbol6->setPos(0.1, -0.1);

  Symbol* symbol7 = SymbolFactory::create("s40", P);
  scene->addItem(symbol7);
  symbol7->setPos(0.2, -0.1);
  
  Symbol* symbol8 = SymbolFactory::create("tri30x60", P);
  scene->addItem(symbol8);
  symbol8->setPos(0.3, -0.1);

  Symbol* symbol9 = SymbolFactory::create("donut_s60x30", P);
  scene->addItem(symbol9);
  symbol9->setPos(0, -0.2);

  Symbol* symbol10 = SymbolFactory::create("hex_l60x60x20", P);
  scene->addItem(symbol10);
  symbol10->setPos(0.1, -0.2);

  Symbol* symbol11 = SymbolFactory::create("hex_s60x60x20", P);
  scene->addItem(symbol11);
  symbol11->setPos(0.2, -0.2);

  Symbol* symbol12 = SymbolFactory::create("bfr60", P);
  scene->addItem(symbol12);
  symbol12->setPos(0.3, -0.2);

  Symbol* symbol13 = SymbolFactory::create("bfs60", P);
  scene->addItem(symbol13);
  symbol13->setPos(0, -0.3);

  Symbol* symbol14 = SymbolFactory::create("oval_h30x60", P);
  scene->addItem(symbol14);
  symbol14->setPos(0.1, -0.3);

  Symbol* symbol15 = SymbolFactory::create("ths60x40x45x4x10", P);
  scene->addItem(symbol15);
  symbol15->setPos(0.2, -0.3);

  widget.show();
  return app.exec();
}

