#include "layer.h"

#include "context.h"

extern Context ctx;

Layer::Layer(QString step, QString layer):
  Features(ctx.loader->featuresPath(
        QString("steps/%1/layers/%2").arg(step).arg(layer))),
  m_step(step), m_layer(layer)
{
}

QString Layer::step()
{
  return m_step;
}

QString Layer::layer()
{
  return m_layer;
}
