#ifndef __ODBPPGRAPHICSVIEW_H__
#define __ODBPPGRAPHICSVIEW_H__

#include <QGraphicsView>
#include "feature.h"
#include "profile.h"

#include "odbppgraphicsscene.h"

class ODBPPGraphicsView: public QGraphicsView {
  Q_OBJECT

public:
  ODBPPGraphicsView(QWidget* parent = 0);
  Features* loadFeature(QString filename, const QColor color = Qt::red,
      const QBrush brush = Qt::red);
  Profile* loadProfile(QString step);
  void clear_scene(){scene->clear();}
  QGraphicsScene *GetScene(){return scene;}
  void addItem(Features *bot){scene->addItem(bot);}
  void removeItem(Features *bot){scene->removeItem(bot);}

protected:
  void wheelEvent(QWheelEvent *event);
  void scaleView(qreal scaleFactor);

private:
  ODBPPGraphicsScene *scene;
};

#endif /* __ODBPPGRAPHICSVIEW_H__ */
