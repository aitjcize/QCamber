#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>

extern Context ctx;
extern Config cfg;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  loadColorConfig();

  for (int i = 0; i < m_colors.size(); ++i) {
    m_colorsMap[i] = false;
  }

  ui->setupUi(this);

  m_layout = new QVBoxLayout();
  m_tool_layout = new QVBoxLayout();
  ui->scrollWidget->setLayout(m_layout);
  ui->groupBox_Tool->setLayout(m_tool_layout);

  load_function_btn();
  connect(&m_color_widget,SIGNAL(selected()),this,SLOT(loadColorConfig()));
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
  QString pathTmpl = "steps/%1/layers/%2";

  for(int i = 0; i < layerNames.count(); ++i)
  {
    LayerSelector *layer = new LayerSelector(layerNames[i],
        pathTmpl.arg(this->windowTitle()).arg(layerNames[i]));

    connect(layer, SIGNAL(Clicked(LayerSelector*, bool)), this,
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
  Features* features = new Features(ctx.loader->featuresPath(path));
  features->setPen(pen);
  features->setBrush(brush);
  return features;
}

void MainWindow::showLayer(LayerSelector* selector, bool selected)
{
  if (!selected) {
    if (!selector->features) {
      selector->features = makeFeature(selector->path(),
          QPen(selector->color(), 0), QBrush(selector->color()));
      ui->viewWidget->addItem(selector->features);
    }
    selector->setColor(nextColor());
    selector->features->setOpacity(1);
  } else {
    int index = m_colors.indexOf(selector->color());
    m_colorsMap[index] = false;
    selector->features->setOpacity(0);
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

void MainWindow::loadColorConfig()
{
  QString color_config;
  if(! m_colors.empty())
    m_colors.clear();
  for(int i=1;i<COLOR_NUMBER+1;i++)
  {
    color_config.sprintf("color/%d",i);
    m_colors<<QColor(cfg.value(color_config).toString());
  }
}

void MainWindow::load_function_btn()
{
  myLabel *label = new myLabel("Set color");
  connect(label,SIGNAL(clicked()),this,SLOT(showColorSelector()));

  m_tool_layout->addWidget(label);
}

void MainWindow::showColorSelector()
{
  m_color_widget.show();
  //loadColorConfig();
}
