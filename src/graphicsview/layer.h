#ifndef __LAYER_H__
#define __LAYER_H__

#include <QGraphicsScene>

#include "layerfeatures.h"
#include "graphicslayer.h"
#include "graphicslayerscene.h"
#include "notes.h"
#include "symbol.h"
#include <QTextEdit>

class Layer: public GraphicsLayer {
public:
  Layer(QString step, QString layer);
  virtual ~Layer();

  QString step();
  QString layer();
  Notes* notes();
  QStandardItemModel* reportModel(void);

  void setHighlightEnabled(bool status);
  void setShowStepRepeat(bool status);

  virtual void setPen(const QPen& pen);
  virtual void setBrush(const QBrush& brush);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  LayerFeatures* m_features;
  QString m_step;
  QString m_layer;
  Notes* m_notes;
};

#endif /* __LAYER_H__ */
