#ifndef __LAYER_H__
#define __LAYER_H__

#include "feature.h"

class Layer: public Features {
public:
  Layer(QString step, QString layer);
  virtual ~Layer();

  QString step();
  QString layer();

  void setOpacity(qreal opacity);
  void setDoComposite(bool status);

private:
  QString m_step;
  QString m_layer;

  LayerGraphicsEffect* m_layerEffect;
};

#endif /* __LAYER_H__ */
