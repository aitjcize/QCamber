#include "mainviewer.h"
#include "ui_mainviewer.h"
#include "QDebug"

extern Context ctx;

mainViewer::mainViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainViewer)
{
    ui->setupUi(this);
    ui->WorkTable->setScene(widget.GetScene());

    ui->WorkTable->scale(100,100);

}

mainViewer::~mainViewer()
{
    delete ui;
}

void mainViewer::addLayerLabel(QList<QString> *layer_name)
{
    layerSignalMapper = new QSignalMapper(this);
    for(int i=0;i<layer_name->length();i++)
    {
        myLabel *layer = new myLabel("this");
        layer->setText((*layer_name)[i]);
        connect(layer, SIGNAL(clicked()),layerSignalMapper, SLOT(map()));
        layerSignalMapper->setMapping(layer,(*layer_name)[i]);

        ui->layerlayout->addWidget(layer);
    }
    connect(layerSignalMapper, SIGNAL(mapped (const QString &)), this, SLOT(ShowLayer(const QString &)));

}

void mainViewer::clearLayerLabel()
{
    clearLayout(ui->layerlayout,true);
}

void mainViewer::clearLayout(QLayout* layout, bool deleteWidgets)
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


void mainViewer::ShowLayer(const QString feature_name)
{

  QString path = "steps/" + this->windowTitle() + "/layers/" + feature_name + "/features";

  path = ctx.loader->absPath(path);
  QFile file(path);
  ui->WorkTable->scene()->clear();
  widget.load_profile(this->windowTitle());
  if (file.exists()) {
    widget.load_feature(path);
  } else {
    widget.load_feature(path + ".Z");
  }

  //widget.show();
}

