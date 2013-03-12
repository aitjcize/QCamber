#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "layerfeatures.h"
#include "graphicslayer.h"
#include "graphicslayerscene.h"
#include "record.h"
#include "symbol.h"

class Profile: public GraphicsLayer {
public:
  Profile(QString step, bool stepRepeat = true);
  virtual ~Profile();

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  LayerFeatures* m_features;
};

#endif /* __PROFILE_H__ */
