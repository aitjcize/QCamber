#ifndef LAYERINFOBOX_H
#define LAYERINFOBOX_H

#include <QColor>
#include <QString>
#include <QWidget>

#include "layer.h"

namespace Ui {
class LayerInfoBox;
}

class LayerInfoBox : public QWidget
{
  Q_OBJECT

public:
  explicit LayerInfoBox(QWidget *parent, const QString& name, QColor color);
  ~LayerInfoBox();

  QString layer(void);
  QColor color(void);

  void setColor(const QColor& color);
  void toggle(void);

  Layer *item;

signals:
  void toggled(bool checked);

public slots:
  void on_activeIndicator_clicked(void);

protected:
  virtual void mousePressEvent(QMouseEvent *ev);
    
private:
  Ui::LayerInfoBox *ui;
  QString m_layer;
  QColor m_color;
  bool m_checked;
};

#endif // LAYERINFOBOX_H
