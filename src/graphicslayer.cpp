#include "graphicslayer.h"

#include <QtGui>

#include "context.h"
#include "odbppgraphicsscene.h"

GraphicsLayer::GraphicsLayer(QGraphicsItem* parent):
  QGraphicsItem(parent), m_showOutline(false)
{
  m_layerScene = NULL;
}

GraphicsLayer::~GraphicsLayer()
{
  if (m_layerScene) {
    delete m_layerScene;
  }
}

void GraphicsLayer::setLayerScene(GraphicsLayerScene* scene)
{
  m_layerScene = scene;
  m_layerScene->setGraphicsLayer(this);
}

QGraphicsScene* GraphicsLayer::layerScene(void)
{
  return m_layerScene;
}

void GraphicsLayer::setViewRect(const QRect& rect)
{
  m_viewRect = rect;
}

void GraphicsLayer::setSceneRect(const QRectF& rect)
{
  m_sceneRect = rect;
}

void GraphicsLayer::setShowOutline(bool status)
{
  m_showOutline = status;
  setBrush(m_brush);
  forceUpdate();
}

void GraphicsLayer::setPen(const QPen& pen)
{
  m_pen = pen;
  QList<QGraphicsItem*> items = m_layerScene->items();
  for (int i = 0; i < items.size(); ++i) {
    dynamic_cast<Symbol*>(items[i])->setPen(pen);
  }
}

void GraphicsLayer::setBrush(const QBrush& brush)
{
  QBrush tbrush = brush;
  m_brush = brush;

  if (m_showOutline) {
    tbrush = Qt::transparent;
  }

  QList<QGraphicsItem*> items = m_layerScene->items();
  for (int i = 0; i < items.size(); ++i) {
    dynamic_cast<Symbol*>(items[i])->setBrush(tbrush);
  }
}

QRectF GraphicsLayer::boundingRect() const
{
  if (m_layerScene) {
    return m_layerScene->itemsBoundingRect();
  } else {
    return QRectF();
  }
}

void GraphicsLayer::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (!m_layerScene) {
    return;
  }

  if (m_prevSceneRect != m_sceneRect) {
    m_pixmap = QPixmap(m_viewRect.size());
    QBitmap alphaMask(m_viewRect.size());
    alphaMask.clear();
    m_pixmap.setMask(alphaMask);

    m_prevSceneRect = m_sceneRect;

    QPainter sourcePainter(&m_pixmap);
    m_layerScene->render(&sourcePainter, m_viewRect, m_sceneRect);
  }

  painter->save();
  painter->setCompositionMode(QPainter::CompositionMode_Difference);
  painter->drawPixmap(m_sceneRect, m_pixmap, m_viewRect);
  painter->restore();
}

void GraphicsLayer::forceUpdate(void)
{
  m_prevSceneRect = QRectF();
  update();
}
