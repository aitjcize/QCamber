#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

extern Context ctx;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->WorkTable->setScene(widget.GetScene());

    ui->WorkTable->scale(100,100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addLayerLabel(QList<QString> *layer_name)
{
    clearLayout(ui->layerlayout,true);
    layerSignalMapper = new QSignalMapper(this);
    for(int i=0;i<layer_name->length();i++)
    {
        LayerSelector *layer = new LayerSelector("this");
        layer->setText((*layer_name)[i]);
        layer->setStyle("LayerSelector { background-color : red; color : blue; }");
        connect(layer, SIGNAL(DoubleClicked()),layerSignalMapper, SLOT(map()));
        layerSignalMapper->setMapping(layer,(*layer_name)[i]);

        ui->layerlayout->addWidget(layer);
    }
    connect(layerSignalMapper, SIGNAL(mapped (const QString &)), this, SLOT(ShowLayer(const QString &)));

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


void MainWindow::ShowLayer(const QString feature_name)
{

  QString path = "steps/" + this->windowTitle() + "/layers/" + feature_name + "/features";

  path = ctx.loader->absPath(path.toLower());
  QFile file(path);
  //ui->WorkTable->scene()->clear();
  widget.load_profile(this->windowTitle());
  if (file.exists()) {
    widget.load_feature(path);
  } else {
    widget.load_feature(path + ".Z");
  }

  //widget.show();
}

