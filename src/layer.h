#ifndef __LAYER_H__
#define __LAYER_H__

#include "feature.h"
#include "notes.h"

class Layer: public Features {
public:
  Layer(QString step, QString layer);
  virtual ~Layer();

  QString step();
  QString layer();
  Notes* notes();

  void setOpacity(qreal opacity);
  void setDoComposite(bool status);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  QString m_step;
  QString m_layer;
  Notes* m_notes;

  LayerGraphicsEffect* m_layerEffect;
};

#endif /* __LAYER_H__ */
