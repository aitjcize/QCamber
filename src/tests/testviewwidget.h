#ifndef __TEST_VIEW_WIDGET_H__
#define __TEST_VIEW_WIDGET_H__

#include <QGraphicsView>
#include <QWheelEvent>

class TestViewWidget: public QGraphicsView {
  Q_OBJECT

public:
    TestViewWidget(QWidget* parent = 0);

protected:
    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);
};

#endif /* __TEST_VIEW_WIDGET_H__ */
