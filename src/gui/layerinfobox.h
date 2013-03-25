#ifndef __LAYERINFOBOX_H__
#define __LAYERINFOBOX_H__

#include <QColor>
#include <QMenu>
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
  explicit LayerInfoBox(const QString& name, const QString& step,
    const QString& type);
  ~LayerInfoBox();

  QString name(void);
  QColor color(void);
  Layer* layer(void);

  void setColor(const QColor& color);
  void setLayer(Layer* layer);

  void toggle(void);
  bool isActive(void);
  void setActive(bool status);

signals:
  void toggled(bool checked);
  void activated(bool status);

public slots:
  void showContextMenu(const QPoint& point);
  void on_activeIndicator_clicked(void);
  void on_actionFeaturesHistogram_activated(void);

protected:
  virtual void mousePressEvent(QMouseEvent *ev);
    
private:
  Ui::LayerInfoBox *ui;
  QString m_name;
  QString m_step;
  QString m_type;
  QColor m_color;
  Layer* m_layer;
  bool m_checked;
  QMenu* m_contextMenu;
};

#endif // __LAYERINFOBOX_H__
