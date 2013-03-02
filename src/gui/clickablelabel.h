#ifndef __CLICKABLE_LABEL_H__
#define __CLICKABLE_LABEL_H__
#include <QLabel>

class ClickableLabel : public QLabel
{
  Q_OBJECT

public:
  ClickableLabel(QWidget* parent = 0);
  ClickableLabel(const QString &text, QWidget *parent = 0);
  void setColor(QString fg, QString bg);

signals:
  void clicked();

protected:
  virtual void mousePressEvent(QMouseEvent *ev);
};

#endif // __CLICKABLE_LABEL_H__
