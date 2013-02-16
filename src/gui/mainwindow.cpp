#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>

extern Context ctx;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  m_colors << QColor::fromRgb(253, 0, 0)  << QColor::fromRgb(74, 165, 2)
    << QColor::fromRgb(0, 173, 199) << QColor::fromRgb(255, 255, 62)
    << Qt::cyan << Qt::magenta << Qt::green << Qt::blue;

  for (int i = 0; i < m_colors.size(); ++i) {
    m_colorsMap[i] = false;
  }

  ui->setupUi(this);

  m_layout = new QVBoxLayout();
  ui->scrollWidget->setLayout(m_layout);
  ui->viewWidget->setBackgroundBrush(BG_COLOR);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::addLayerLabel(const QStringList& layerNames)
{
  ui->viewWidget->clear_scene();
  ui->viewWidget->loadProfile(this->windowTitle());

  clearLayout(m_layout, true);
  QString pathTmpl = "steps/%1/layers/%2/features";

  for(int i = 0; i < layerNames.count(); ++i)
  {
    LayerSelector *layer = new LayerSelector(layerNames[i],
        pathTmpl.arg(this->windowTitle()).arg(layerNames[i]));

    connect(layer, SIGNAL(doubleClicked(LayerSelector*, bool)), this,
        SLOT(showLayer(LayerSelector*, bool)));
    m_layout->addWidget(layer);
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

void MainWindow::showLayer(LayerSelector* selector, bool selected)
{
  if (!selector->features) {
    selector->features = makeFeature(selector->path(),
        QPen(selector->color(), 0), QBrush(selector->color()));
  }

  if(!selected) {
    selector->setColor(nextColor());
    ui->viewWidget->addItem(selector->features);
  } else {
    int index = m_colors.indexOf(selector->color());
    m_colorsMap[index] = false;
    ui->viewWidget->removeItem(selector->features);
  }
}

QColor MainWindow::nextColor(void)
{
  for (int i = 0; i < m_colors.size(); ++i) {
    if (!m_colorsMap[i]) {
      m_colorsMap[i] = true;
      return m_colors[i];
    }
  }
  return Qt::red;
}
