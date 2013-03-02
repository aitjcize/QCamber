#include "odbppgraphicsminimapview.h"

#include "symbolfactory.h"
#include "context.h"

ODBPPGraphicsMiniMapView::ODBPPGraphicsMiniMapView(QWidget* parent):
  QGraphicsView(parent),
  m_profile(NULL)
{
  m_scene = new ODBPPGraphicsScene(this);
  m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  m_scene->setBackgroundBrush(ctx.bg_color);
  m_scene->setSceneRect(-800, -600, 1600, 1200);
  m_scene->setAreaZoomEnabled(true);
  setScene(m_scene);
  setDragMode(NoDrag);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setCacheMode(CacheBackground);
  setOptimizationFlags(DontSavePainterState);
  setTransformationAnchor(AnchorUnderMouse);
  setViewportUpdateMode(BoundingRectViewportUpdate);

  m_rect = new QGraphicsRectItem;
  m_rect->setPen(QPen(Qt::red, 0));
  m_rect->setBrush(QColor(255, 0, 0, 128));
  m_scene->addItem(m_rect);

  connect(m_scene, SIGNAL(rectSelected(QRectF)), this,
      SLOT(zoomMainViewToRect(QRectF)));
}

ODBPPGraphicsMiniMapView::~ODBPPGraphicsMiniMapView()
{
  delete m_scene;
}

void ODBPPGraphicsMiniMapView::scaleView(qreal scaleFactor)
{
  scale(scaleFactor, scaleFactor);
}

void ODBPPGraphicsMiniMapView::loadProfile(QString step)
{
  QString path;
  path = QString("steps/%1/profile").arg(step.toLower());
  m_profile = new Profile(ctx.loader->absPath(path));

  QColor color(255 - ctx.bg_color.red(), 255 - ctx.bg_color.green(),
      255 - ctx.bg_color.blue(), 255);

  m_profile->setPen(QPen(color, 0));
  m_profile->setBrush(Qt::transparent);
  m_scene->addItem(m_profile);

  m_rect->setRect(m_profile->boundingRect());
}

void ODBPPGraphicsMiniMapView::setBackgroundColor(QColor color)
{
  m_scene->setBackgroundBrush(color);

  if (m_profile) {
    QColor color(255 - ctx.bg_color.red(), 255 - ctx.bg_color.green(),
        255 - ctx.bg_color.blue(), 255);
    m_profile->setPen(QPen(color, 0));
    m_profile->setBrush(Qt::transparent);
  }
}

void ODBPPGraphicsMiniMapView::zoomToAll(void)
{
  zoomToRect(m_profile->boundingRect());
}

void ODBPPGraphicsMiniMapView::zoomToRect(QRectF rect)
{
  QRectF b = rect.normalized();
  QRectF current = transform().mapRect(QRectF(0, 0, 1, 1));
  QRectF vp = viewport()->rect();

  qreal sx = vp.width() / (current.width() * b.width() * 1.1);
  qreal sy = vp.height() / (current.height() * b.height() * 1.1);
  qreal s = qMin(sx, sy);

  scaleView(s);
  centerOn(b.center());
}

void ODBPPGraphicsMiniMapView::zoomMainViewToRect(QRectF rect)
{
  m_rect->setRect(rect);
  emit minimapRectSelected(rect);
}

void ODBPPGraphicsMiniMapView::redrawSceneRect(QRectF rect)
{
  m_rect->setRect(rect);
}

void ODBPPGraphicsMiniMapView::wheelEvent(QWheelEvent* event)
{
  // Do nothing
}
