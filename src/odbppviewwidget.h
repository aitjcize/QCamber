#ifndef __ODBPP_VIEW_WIDGET_H__
#define __ODBPP_VIEW_WIDGET_H__

#include <QtGui/QGraphicsView>

class ODBPPViewWidget: public QGraphicsView {
  Q_OBJECT
private:
    QGraphicsScene *scene;
public:
    ODBPPViewWidget(QWidget* parent = 0);
    void load_feature(QString);
protected:
    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);
};

#endif /* __ODBPP_VIEW_WIDGET_H__ */
