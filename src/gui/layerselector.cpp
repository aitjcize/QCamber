#include "layerselector.h"
#include "QDebug"
#include "QMenu"

  LayerSelector::LayerSelector(const QString &text,QWidget *parent)
:QLabel(parent)
{
  isSelected = 0;
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
      this, SLOT(show_contextmenu(const QPoint&)));
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
  emit DoubleClicked(bot,isSelected);
  isSelected = !isSelected;
}

void LayerSelector::show_contextmenu(const QPoint &point)
{

  QMenu *cmenu = new QMenu();
  colorSignalMapper = new QSignalMapper(this);
  QAction *ascendSortAction;

  ascendSortAction = cmenu->addAction("cyan");
  connect(ascendSortAction, SIGNAL(triggered(bool)),colorSignalMapper, SLOT(map()));
  colorSignalMapper->setMapping(ascendSortAction,"cyan");

  ascendSortAction = cmenu->addAction("red");
  connect(ascendSortAction, SIGNAL(triggered(bool)),colorSignalMapper, SLOT(map()));
  colorSignalMapper->setMapping(ascendSortAction,"red");

  ascendSortAction = cmenu->addAction("magenta");
  connect(ascendSortAction, SIGNAL(triggered(bool)),colorSignalMapper, SLOT(map()));
  colorSignalMapper->setMapping(ascendSortAction,"magenta");

  ascendSortAction = cmenu->addAction("green");
  connect(ascendSortAction, SIGNAL(triggered(bool)),colorSignalMapper, SLOT(map()));
  colorSignalMapper->setMapping(ascendSortAction,"green");

  ascendSortAction = cmenu->addAction("yellow");
  connect(ascendSortAction, SIGNAL(triggered(bool)),colorSignalMapper, SLOT(map()));
  colorSignalMapper->setMapping(ascendSortAction,"yellow");

  ascendSortAction = cmenu->addAction("blue");
  connect(ascendSortAction, SIGNAL(triggered(bool)),colorSignalMapper, SLOT(map()));
  colorSignalMapper->setMapping(ascendSortAction,"blue");


  connect(colorSignalMapper, SIGNAL(mapped (const QString &)), this, SLOT(colorSelector(const QString &)));
  cmenu->exec(QCursor::pos());
}
void LayerSelector::colorSelector(const QString &color)
{
  QString tcolor = "black";
  if(color == "green" || color == "blue")
    tcolor = "white";
  BGstyle = "QLabel { background-color : "+color+"; color : "+tcolor+"; }";
  bot->setPen(QPen(QColor(color), 0));
  bot->setBrush(QColor(color));
  if(isSelected)
  {
    setStyleSheet(BGstyle);
    emit DoubleClicked(bot,isSelected);
    emit DoubleClicked(bot,!isSelected);
  }

}
