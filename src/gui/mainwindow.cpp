#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QFile"

extern Context ctx;


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->viewWidget->setBackgroundBrush(Qt::black);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::addLayerLabel(const QStringList& layerNames)
{
  //1.把label建立起來
  //2.把FEATURE存起來
  //3.設定connect

  ui->viewWidget->clear_scene();
  addProfile();

  QString color = "cyan,red,magenta,green,yellow,blue";
  QStringList labelcolor = color.split(',');

  clearLayout(ui->layerLayout, true);
  QString pathTmpl = "steps/%1/layers/%2/features";

  for(int i = 0; i < layerNames.count(); ++i)
  {
    LayerSelector *layer = new LayerSelector(layerNames[i], labelcolor[i % 6],
        pathTmpl.arg(this->windowTitle()).arg(layerNames[i]));

    connect(layer, SIGNAL(doubleClicked(LayerSelector*, bool)), this,
        SLOT(showLayer(LayerSelector*, bool)));
    ui->layerLayout->addWidget(layer);
  }
}

void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
  while (QLayoutItem* item = layout->takeAt(0))
  {
    if (deleteWidgets)
    {
      if (QWidget* widget = item->widget())
        delete widget;
    }
    else if (QLayout* childLayout = item->layout())
      clearLayout(childLayout, deleteWidgets);
    delete item;
  }
}


Features* MainWindow::makeFeature(QString path, const QPen& pen,
    const QBrush& brush)
{
  //QString path = "steps/" + this->windowTitle() + "/layers/" + filename + "/features";
  path = ctx.loader->absPath(path.toLower());
  QFile file(path);
  //ui->viewWidget->scene()->clear();
  //把profile變成按鈕
  //widget.load_profile(this->windowTitle());
  if (!file.exists())
  {
    file.setFileName(path + ".Z");
    if (!file.exists())
      path += ".z";
    else
      path += ".Z";
  }
  //qDebug()<<path;

  Features* features = new Features(path);
  features->setPen(pen);
  features->setBrush(brush);
  return features;
}

void MainWindow::showLayer(LayerSelector* selector, bool isSelected)
{
  if (!selector->features) {
    selector->features = makeFeature(selector->path(),
        QPen(selector->color(), 0), QBrush(selector->color()));
  }

  if(!isSelected) {
    ui->viewWidget->addItem(selector->features);
  } else {
    ui->viewWidget->removeItem(selector->features);
  }
}

void MainWindow::addProfile()
{
  QString path = "steps/" + this->windowTitle() + "/profile";
  path = ctx.loader->absPath(path.toLower());
  Features* features = new Features(path);
  features->setPen(QPen(Qt::white, 0));
  features->setBrush(Qt::transparent);
  ui->viewWidget->addItem(features);
}
