#include "colorsettings.h"

#include <QtGui>

#include "ui_colorsettings.h"
#include "mylabel.h"

extern Config cfg;

ColorSettings::ColorSettings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ColorSettings)
{
  ui->setupUi(this);

  //writeToconfig();
  colorSignalMapper = new QSignalMapper(this);

  QString label_name;
  for(int i=1;i<COLOR_NUMBER+1;i++)
  {
    label_name.sprintf("%d",i);
    myLabel *label = new myLabel(label_name);
    label->setStyleSheet("QLabel { background-color: " + cfg.value("color/" +
          label_name).toString() + "; color: black; }");
    connect(label, SIGNAL(clicked()),colorSignalMapper, SLOT(map()));
    colorSignalMapper->setMapping(label,label_name);
    label_list.append(label);
    ui->horizontalLayout->addWidget(label);
  }
  connect(colorSignalMapper, SIGNAL(mapped(const QString &)), this,
      SLOT(openSelector(const QString &)));
  //connect(colorSignalMapper,SIGNAL(mapped(QWidget*)),this,SLOT(openSelector(QWidget*)));
}

ColorSettings::~ColorSettings()
{
  delete ui;
}

QColor ColorSettings::openSelector(const QString  color_config)
{
  QColorDialog colorSelector;
  QColor color(cfg.value("color/"+color_config).toString());
  //QColorDialog::setCustomColor(0, QRgb(0x0000FF));
  //QColor color = QColorDialog::getColor(QColor(0, 255, 0));
  colorSelector.setCurrentColor(color);
  color = colorSelector.getColor(QColor(0,255,0));
  cfg.setValue("color/"+color_config,color.name());
  label_list.at(color_config.toInt()-1)->setStyleSheet(
      "QLabel { background-color: " + color.name() + "; color: black; }");
  return color;
}

void ColorSettings::writeToconfig()
{
  QString text;
  for (int i = 1; i < COLOR_NUMBER+1; i++) {
    text.sprintf("color/%d",i);
    cfg.setValue(text,QColor("#FF00FF").name());
    //qDebug()<<QColor("#FF00FF").name();
  }
}

void ColorSettings::on_buttonBox_accepted()
{
  emit selected();
}
