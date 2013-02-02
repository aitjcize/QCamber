#ifndef __ODBPP_VIEW_WIDGET_H__
#define __ODBPP_VIEW_WIDGET_H__

#include <QtGui/QGraphicsView>

class ODBPPViewWidget: public QGraphicsView {
  Q_OBJECT

public:
    ODBPPViewWidget(QWidget* parent = 0);
};

#endif /* __ODBPP_VIEW_WIDGET_H__ */
