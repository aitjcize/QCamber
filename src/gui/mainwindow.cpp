#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>

#include "context.h"

extern Context ctx;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  loadColorConfig();

  for (int i = 0; i < m_colors.size(); ++i) {
    m_colorsMap[i] = false;
  }

  m_statusLabel = new myLabel("status bar");
  ui->statusbar->addWidget(m_statusLabel);
  m_layout = new QVBoxLayout();
  m_tool_layout = new QVBoxLayout();
  ui->scrollWidget->setLayout(m_layout);
  ui->groupBox_Tool->setLayout(m_tool_layout);

  connect(&m_color_widget, SIGNAL(selected()), this, SLOT(loadColorConfig()));

  connect(ui->viewWidget->scene(), SIGNAL(mouseMove(QPointF)), this,
      SLOT(showMouseCord(QPointF)));
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
    selector->features->setDoComposite(true);
  } else {
    int index = m_colors.indexOf(selector->color());
    m_colorsMap[index] = false;
    selector->features->setDoComposite(false);
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
  ctx.bg_color = QColor(ctx.config->value("color/BG").toString());
  ui->viewWidget->setBackgroundColor(ctx.bg_color);

  QString config("color/%1");
  m_colors.clear();

  for(int i = 1; i < COLOR_NUMBER + 1; i++) {
    m_colors << QColor(ctx.config->value(config.arg(i)).toString());
  }

  for (int i = 0; i < m_colors.size(); ++i) {
    m_colorsMap[i] = false;
  }
}

void MainWindow::on_actionSetColor_triggered()
{
  m_color_widget.show();
}

void MainWindow::showMouseCord(QPointF pos)
{
  QString text;
  text.sprintf("(%f, %f)", pos.x(), pos.y());
  m_statusLabel->setText(text);
}

