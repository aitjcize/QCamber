#ifndef __ODBPP_VIEW_WIDGET_H__
#define __ODBPP_VIEW_WIDGET_H__

#include <QGraphicsView>

class ODBPPViewWidget: public QGraphicsView {
  Q_OBJECT

public:
    ODBPPViewWidget(QWidget* parent = 0);

protected:
    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);
};

#endif /* __ODBPP_VIEW_WIDGET_H__ */
