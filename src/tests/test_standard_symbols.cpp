#include "testviewwidget.h"

#include "testviewwidget.h"
#include "archiveloader.h"
#include "symbolfactory.h"
#include "context.h"

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

  Symbol* symbol16 = SymbolFactory::create("thr60x40x45x4x10", P);
  scene->addItem(symbol16);
  symbol16->setPos(0.3, -0.3);

  Symbol* symbol17 = SymbolFactory::create("s_ths60x40x45x4x10", P);
  scene->addItem(symbol17);
  symbol17->setPos(0.4, 0.0);

  Symbol* symbol18 = SymbolFactory::create("s_tho60x40x45x4x10", P);
  scene->addItem(symbol18);
  symbol18->setPos(0.4, -0.1);

  Symbol* symbol19 = SymbolFactory::create("sr_ths60x40x45x4x10", P);
  scene->addItem(symbol19);
  symbol19->setPos(0.4, -0.2);

  Symbol* symbol20 = SymbolFactory::create("rc_ths60x40x45x4x10x10", P);
  scene->addItem(symbol20);
  symbol20->setPos(0.4, -0.3);

  Symbol* symbol21 = SymbolFactory::create("rc_tho60x40x45x4x10x5", P);
  scene->addItem(symbol21);
  symbol21->setPos(0.5, 0.0);

  Symbol* symbol22 = SymbolFactory::create("el60x30", P);
  scene->addItem(symbol22);
  symbol22->setPos(0.5, -0.1);

  Symbol* symbol23 = SymbolFactory::create("moire5x10x4x4x100x0", P);
  scene->addItem(symbol23);
  symbol23->setPos(0.5, -0.2);

  Symbol* symbol24 = SymbolFactory::create("hole50xpx4x5", P);
  scene->addItem(symbol24);
  symbol24->setPos(0.5, -0.3);

  Symbol* symbol25 = SymbolFactory::create("null1", P);
  scene->addItem(symbol25);
  symbol25->setPos(0.6, 0.0);

  widget.show();
  return app.exec();
}

