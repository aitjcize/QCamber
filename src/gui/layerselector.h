#ifndef __LAYERSELECTOR_H__
#define __LAYERSELECTOR_H__

#include <QLabel>
#include <QSignalMapper>

#include "layer.h"

class LayerSelector : public QLabel
{
  Q_OBJECT

public:
  LayerSelector(const QString& text, const QString& step, const QString& layer,
      QWidget *parent = 0);
  ~LayerSelector();

  QColor color(void);
  QString step(void);
  QString layer(void);

  void setColor(const QColor& color);

  Layer *item;

signals:
  void Clicked(LayerSelector*, bool);

private slots:
  void colorSelector(const QString&);

protected:
  void mousePressEvent(QMouseEvent *ev);

private:
  bool m_selected;
  QString m_bgStyle;
  QString m_bgStyleTmpl;

  QString m_step;
  QString m_layer;
  QColor m_color;
  QSignalMapper* m_colorSignalMapper;
};

#endif // __LAYERSELECTOR_H__
