#include "layerselector.h"
#include "QDebug"

LayerSelector::LayerSelector(const QString &text,QWidget *parent)
    :QLabel(parent)
{
    isSelected = 0;
}

void LayerSelector::slotClicked()
{
    qDebug()<<"QQ";
}

void LayerSelector::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
}

void LayerSelector::mouseDoubleClickEvent(QMouseEvent *)
{
    if(!isSelected)
        setStyleSheet(BGstyle);
    else
        setStyleSheet("QLabel { background-color : transparent; color : black; }");
    isSelected = !isSelected;
    emit DoubleClicked();
}
