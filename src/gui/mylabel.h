#ifndef MYLABEL_H
#define MYLABEL_H
#include "QLabel"

class myLabel : public QLabel
{
  Q_OBJECT

public:
  myLabel(const QString &text,QWidget *parent = 0);
  ~myLabel(){}

signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent *ev);
};

#endif // MYLABEL_H
