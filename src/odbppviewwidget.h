#ifndef __ODBPP_VIEW_WIDGET_H__
#define __ODBPP_VIEW_WIDGET_H__

#include <QGraphicsView>

class ODBPPViewWidget: public QGraphicsView {
  Q_OBJECT

public:
  ODBPPViewWidget(QWidget* parent = 0);
  void load_feature(QString filename);
  void load_profile(QString step);
  void clear_scene(){scene->clear();}

protected:
  void wheelEvent(QWheelEvent *event);
  void scaleView(qreal scaleFactor);

private:
  QGraphicsScene *scene;
};

#endif /* __ODBPP_VIEW_WIDGET_H__ */
