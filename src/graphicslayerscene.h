#ifndef __GRAPHICSLAYERSCENE__
#define __GRAPHICSLAYERSCENE__

#include <QGraphicsScene>
#include <QList>

#include "symbol.h"

class GraphicsLayer;

class GraphicsLayerScene: public QGraphicsScene {
  Q_OBJECT

public:
  GraphicsLayerScene(QObject* parent = 0);
  virtual ~GraphicsLayerScene();

  void setGraphicsLayer(GraphicsLayer* layer);
  bool highlight(void);
  void setHighlight(bool status);
  void clearHighlight(void);

  void updateSelection(Symbol* symbol);

signals:
  void featureSelected(Symbol*);
  
private:
  GraphicsLayer* m_graphicsLayer;
  bool m_highlight;
  QList<Symbol*> m_selectedSymbols;
};

#endif /* __GRAPHICSLAYERSCENE__ */
