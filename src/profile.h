#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <QString>
#include <QGraphicsScene>
#include <QList>

#include "feature.h"
#include "graphicslayer.h"
#include "graphicslayerscene.h"
#include "record.h"
#include "symbol.h"

class Profile: public GraphicsLayer {
public:
  Profile(QString step);
  virtual ~Profile();

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
  Features* m_features;
};

#endif /* __PROFILE_H__ */
