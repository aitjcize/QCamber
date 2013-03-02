#ifndef __LAYER_H__
#define __LAYER_H__

#include <QGraphicsScene>

#include "feature.h"
#include "graphicslayer.h"
#include "graphicslayerscene.h"
#include "notes.h"
#include "symbol.h"

class Layer: public GraphicsLayer {
public:
  Layer(QString step, QString layer);
  virtual ~Layer();

  QString step();
  QString layer();
  Notes* notes();

  void setHighlight(bool status);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  Features* m_features;
  QString m_step;
  QString m_layer;
  Notes* m_notes;
};

#endif /* __LAYER_H__ */
