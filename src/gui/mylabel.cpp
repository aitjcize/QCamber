#include "mylabel.h"
#include "QDebug"
#include "QMouseEvent"

  myLabel::myLabel(const QString &text,QWidget *parent)
:QLabel(parent)
{
  setText(text);
  //connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
}


void myLabel::mousePressEvent(QMouseEvent *ev)
{
  if( ev->button() != Qt::LeftButton)
      return;
  emit clicked();
}
