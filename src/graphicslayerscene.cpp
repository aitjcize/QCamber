#include "graphicslayerscene.h"

#include <QtGui>

#include "graphicslayer.h"

GraphicsLayerScene::GraphicsLayerScene(QObject* parent):
  QGraphicsScene(parent), m_highlight(false)
{
}

void GraphicsLayerScene::setGraphicsLayer(GraphicsLayer* layer)
{
  m_graphicsLayer = layer;
}

bool GraphicsLayerScene::highlight(void)
{
  return m_highlight;
}

void GraphicsLayerScene::setHighlight(bool status)
{
  m_highlight = status;

  if (!status) {
    clearHighlight();
  }
}

void GraphicsLayerScene::clearHighlight(void)
{
  for (int i = 0; i < m_selectedSymbols.size(); ++i) {
    m_selectedSymbols[i]->restoreColor();
  }
  m_selectedSymbols.clear();
  m_graphicsLayer->forceUpdate();
}

void GraphicsLayerScene::updateSelection(Symbol* symbol)
{
  clearHighlight();
  m_selectedSymbols.append(symbol);
  emit featureSelected(symbol);
}
