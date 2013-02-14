#include "mylabel.h"
#include "QDebug"

myLabel::myLabel(const QString &text,QWidget *parent)
    :QLabel(parent)
{
    setText(text);
    //connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
}

void myLabel::slotClicked()
{
    qDebug()<<"QQ";
}

void myLabel::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
}
