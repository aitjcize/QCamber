#ifndef __LAYER_H__
#define __LAYER_H__

#include "feature.h"

class Layer: public Features {
public:
  Layer(QString step, QString layer);

  QString step();
  QString layer();

private:
  QString m_step;
  QString m_layer;
};

#endif /* __LAYER_H__ */
