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
    ui->WorkTable->setBackgroundBrush(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addLayerLabel(QList<QString> *layer_name)
{
    //1.把label建立起來
    //2.把FEATURE存起來
    //3.設定connect
    ui->WorkTable->clear_scene();
    QString color = "cyan,red,magenta,green,yellow,blue";
    QStringList labelcolor = color.split(',');
    QString tcolor = "black,black,black,white,black,white";
    QStringList textcolor = tcolor.split(',');

    clearLayout(ui->layerlayout,true);
    for(int i=0;i<layer_name->length();i++)
    {
        LayerSelector *layer = new LayerSelector("this");
        layer->setText((*layer_name)[i]);
        //要改變label，還有FEATURE的背景顏色
        layer->setStyle("LayerSelector { background-color : "+labelcolor[i%6]+"; color : "+textcolor[i%6]+"; }");
        layer->bot = MakeFeature((*layer_name)[i],QColor(labelcolor[i%6]),QColor(labelcolor[i%6]));
        connect(layer,SIGNAL(DoubleClicked(Features*,int)),this,SLOT(ShowLayer(Features*,int)));
        ui->layerlayout->addWidget(layer);
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


Features *MainWindow::MakeFeature(QString filename,const QColor color,const QBrush brush)
{

  QString path = "steps/" + this->windowTitle() + "/layers/" + filename + "/features";
  path = ctx.loader->absPath(path.toLower());
  QFile file(path);
  //ui->WorkTable->scene()->clear();
  //把profile變成按鈕
  //widget.load_profile(this->windowTitle());
  if (file.exists() == false)
  {
      file.setFileName(path+".Z");
      if (file.exists() == false)
          path += ".z";
      else
          path += ".Z";
  }
  //qDebug()<<path;

  Features* bot = new Features(path);
  bot->setPen(QPen(color, 0));
  bot->setBrush(brush);
  return bot;
}

void MainWindow::ShowLayer(Features *bot, int isSelected)
{
    if(!isSelected)
        ui->WorkTable->addItem(bot);
    else
        ui->WorkTable->removeItem(bot);
}
