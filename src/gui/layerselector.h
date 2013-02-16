#ifndef __LAYERSELECTOR_H__
#define __LAYERSELECTOR_H__

#include <QLabel>
#include <QSignalMapper>

#include "feature.h"

class LayerSelector : public QLabel
{
  Q_OBJECT

public:
  LayerSelector(const QString& text, const QString& color, const QString& path,
      QWidget *parent = 0);
  ~LayerSelector(){}

  QColor color(void);
  QString path(void);

  Features *features;

signals:
  void doubleClicked(LayerSelector*, bool);

private slots:
  void slotClicked();
  void show_contextmenu(const QPoint&);
  void colorSelector(const QString &);

protected:
  void mouseDoubleClickEvent(QMouseEvent *);

private:
  bool m_selected;
  QString m_bgStyle;
  QString m_bgStyleTmpl;

  QString m_path;
  QColor m_color;
  QSignalMapper* m_colorSignalMapper;
};

#endif // __LAYERSELECTOR_H__
