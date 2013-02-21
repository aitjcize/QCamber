#include "layergraphicseffect.h"

#include <QtGui>

LayerGraphicsEffect::LayerGraphicsEffect(QObject* parent):
  QGraphicsEffect(parent), m_opacity(1), m_isFullyOpaque(true),
  m_isFullyTransparent(false), m_doComposite(false)
{
  
}

void LayerGraphicsEffect::draw(QPainter* painter)
{
  if (!m_doComposite) {
    if (m_isFullyTransparent)
      return;

    if (m_isFullyOpaque) {
      drawSource(painter);
      return;
    }
  }

  QPoint offset;
  Qt::CoordinateSystem system = sourceIsPixmap() ? Qt::LogicalCoordinates:
    Qt::DeviceCoordinates;
  QPixmap pixmap = sourcePixmap(system, &offset, QGraphicsEffect::NoPad);
  if (pixmap.isNull())
    return;

  painter->save();

  if (m_doComposite) {
    painter->setCompositionMode(QPainter::CompositionMode_Exclusion);
  }
  if (!m_isFullyTransparent) {
    painter->setOpacity(m_opacity);
  }

  if (system == Qt::DeviceCoordinates) {
      painter->setWorldTransform(QTransform());
  }

  painter->drawPixmap(offset, pixmap);
  painter->restore();
}

void LayerGraphicsEffect::setDoComposite(bool status)
{
  m_doComposite = status;
  update();
}

void LayerGraphicsEffect::setOpacity(qreal opacity)
{
  opacity = qBound(qreal(0.0), opacity, qreal(1.0));

  if (qFuzzyCompare(m_opacity, opacity)) {
    return;
  }

  m_opacity = opacity;
  if ((m_isFullyTransparent = qFuzzyIsNull(m_opacity))) {
    m_isFullyOpaque = 0;
  } else {
    m_isFullyOpaque = qFuzzyIsNull(m_opacity- 1);
  }
  update();
}
