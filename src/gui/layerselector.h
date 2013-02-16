#ifndef LAYERSELECTOR_H
#define LAYERSELECTOR_H
#include "QLabel"
#include "feature.h"
#include "QSignalMapper"

class LayerSelector : public QLabel
{
  Q_OBJECT
public:
  LayerSelector(const QString &text,QWidget *parent = 0);
  ~LayerSelector(){}
  void setStyle(QString style){BGstyle = style;}
  Features *bot;

signals:
  void clicked();
  void DoubleClicked(Features*,int);

private slots:
  void slotClicked();
  void show_contextmenu(const QPoint&);
  void colorSelector(const QString &);

protected:
  void mousePressEvent(QMouseEvent *ev);
  void mouseDoubleClickEvent(QMouseEvent *);

private:
  int isSelected;
  QString BGstyle;
  QSignalMapper *colorSignalMapper;
};

#endif // LAYERSELECTOR_H
