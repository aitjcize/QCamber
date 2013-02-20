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

  colorSignalMapper = new QSignalMapper(this);

  QString label_name;
  for(int i=1;i<COLOR_NUMBER+2;i++)
  {
    label_name.sprintf("%d",i);
    if(i == COLOR_NUMBER + 1)
    label_name = "BG";
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
}

ColorSettings::~ColorSettings()
{
  delete ui;
}

QColor ColorSettings::openSelector(const QString  color_config)
{
  QColorDialog colorSelector;
  QColor color(cfg.value("color/"+color_config).toString());
  colorSelector.setCurrentColor(color);
  color = colorSelector.getColor(QColor(0,255,0));
  cfg.setValue("color/"+color_config,color.name());
  if(color_config == "BG")
    label_list.at(COLOR_NUMBER)->setStyleSheet(
      "QLabel { background-color: " + color.name() + "; color: black; }");
  else
    label_list.at(color_config.toInt()-1)->setStyleSheet(
      "QLabel { background-color: " + color.name() + "; color: black; }");
  return color;
}

void ColorSettings::on_buttonBox_accepted()
{
  emit selected();
}
