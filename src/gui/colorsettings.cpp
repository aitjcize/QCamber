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
    QString color = cfg.value("color/" + label_name).toString();
    label->setStyleSheet("QLabel { background-color: " +
                         color + "; color: " + color + "; }");
    connect(label, SIGNAL(clicked()),colorSignalMapper, SLOT(map()));
    colorSignalMapper->setMapping(label,label_name);
    label_list.append(label);
    myLabel *tlabel = new myLabel(label_name);
    ui->gridLayout_2->addWidget(tlabel,0,i);
    ui->gridLayout_2->addWidget(label,1,i);
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
      "QLabel { background-color: " + color.name() + "; color: "
                + color.name() + "; }");
  else
    label_list.at(color_config.toInt()-1)->setStyleSheet(
      "QLabel { background-color: " + color.name() + "; color: "
                + color.name() + "; }");
  return color;
}

void ColorSettings::on_buttonBox_accepted()
{
  emit selected();
}
