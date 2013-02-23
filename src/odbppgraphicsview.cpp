#include "odbppgraphicsview.h"

#include "symbolfactory.h"
#include "context.h"

extern Context ctx;

ODBPPGraphicsView::ODBPPGraphicsView(QWidget* parent): QGraphicsView(parent),
  m_profile(NULL)
{
  m_scene = new ODBPPGraphicsScene(this);
  m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  m_scene->setSceneRect(-800, -800, 1600, 1600);
  m_scene->setBackgroundBrush(ctx.bg_color);
  setScene(m_scene);

  //setRenderHint(QPainter::Antialiasing);
  setCacheMode(CacheBackground);
  setMinimumSize(600, 600);
  setOptimizationFlags(DontSavePainterState);
  setTransformationAnchor(AnchorUnderMouse);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setZoomMode(AreaZoom);

  connect(m_scene, SIGNAL(rectSelected(QRectF)),
      this, SLOT(zoomToRect(QRectF)));
}

ODBPPGraphicsView::~ODBPPGraphicsView()
{
  delete m_scene;
}

void ODBPPGraphicsView::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor,
      scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

  if (factor > 11050)
      return;

  scale(scaleFactor, scaleFactor);
}

void ODBPPGraphicsView::setZoomMode(ZoomMode mode)
{
  m_zoomMode = mode;
  if (mode == AreaZoom) {
    m_scene->setAreaZoomEnabled(true);
    setDragMode(RubberBandDrag);
  } else {
    m_scene->setAreaZoomEnabled(false);
    setDragMode(ScrollHandDrag);
  }
}

void ODBPPGraphicsView::clearScene(void)
{
  m_scene->clear();
}

void ODBPPGraphicsView::addItem(Symbol* symbol)
{
  m_scene->addItem(symbol);
}

void ODBPPGraphicsView::removeItem(Symbol* symbol)
{
  m_scene->removeItem(symbol);
}

void ODBPPGraphicsView::loadProfile(QString step)
{
  QString path;
  path = QString("steps/%1/profile").arg(step.toLower());
  m_profile = new Profile(ctx.loader->absPath(path));

  QColor color(255 - ctx.bg_color.red(), 255 - ctx.bg_color.green(),
      255 - ctx.bg_color.blue(), 255);

  m_profile->setPen(QPen(color, 0));
  m_profile->setBrush(Qt::transparent);

  m_scene->addItem(m_profile);
  zoomToProfile();
}

void ODBPPGraphicsView::setBackgroundColor(QColor color)
{
  m_scene->setBackgroundBrush(color);

  if (m_profile) {
    QColor color(255 - ctx.bg_color.red(), 255 - ctx.bg_color.green(),
        255 - ctx.bg_color.blue(), 255);
    m_profile->setPen(QPen(color, 0));
    m_profile->setBrush(Qt::transparent);
  }
}

void ODBPPGraphicsView::zoomToProfile(void)
{
  zoomToRect(m_profile->boundingRect());
}

void ODBPPGraphicsView::zoomToRect(QRectF rect)
{
  QRectF b = rect.normalized();
  QRectF current = transform().mapRect(QRectF(0, 0, 1, 1));

  qreal sx = width() / (current.width() * b.width() * 1.1);
  qreal sy = height() / (current.height() * b.height() * 1.1);
  qreal s = qMin(sx, sy);

  qreal factor = transform().scale(s, s).mapRect(QRectF(0, 0, 1, 1)).width();

  if (factor > 8000) {
    s = 8000 / current.width();
  }

  scale(s, s);

  centerOn(b.center());
}

void ODBPPGraphicsView::wheelEvent(QWheelEvent *event)
{
  scaleView(pow((double)2, -event->delta() / 240.0));
}

void ODBPPGraphicsView::keyPressEvent(QKeyEvent* event)
{
  switch (event->key()) {
  case Qt::Key_Home:
    zoomToProfile();
    return;
  case Qt::Key_PageUp:
    scaleView(2);
    return;
  case Qt::Key_PageDown:
    scaleView(0.5);
    return;
  }
  QGraphicsView::keyPressEvent(event);
}
