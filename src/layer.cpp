#include "layer.h"

#include "context.h"

extern Context ctx;

Layer::Layer(QString step, QString layer):
  Features(ctx.loader->featuresPath(
        QString("steps/%1/layers/%2").arg(step).arg(layer))),
  m_step(step), m_layer(layer)
{
  m_layerEffect = new LayerGraphicsEffect();
  setGraphicsEffect(m_layerEffect);
}

Layer::~Layer()
{
  delete m_layerEffect;
}

QString Layer::step()
{
  return m_step;
}

QString Layer::layer()
{
  return m_layer;
}


void Layer::setOpacity(qreal opacity)
{
  m_layerEffect->setOpacity(opacity);
}

void Layer::setDoComposite(bool status)
{
  m_layerEffect->setDoComposite(status);
}
