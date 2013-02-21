#include "colorsettings.h"
#include "ui_colorsettings.h"

#include <QtGui>

#include "clickablelabel.h"
#include "context.h"

extern Context ctx;

ColorSettings::ColorSettings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ColorSettings)
{
  ui->setupUi(this);

  m_colorSignalMapper = new QSignalMapper(this);

  QString label_name;
  for(int i = 1; i < N_COLOR + 2; ++i)
  {
    label_name.sprintf("C%d", i);
    if (i == N_COLOR + 1) {
      label_name = "BG";
    }
    ClickableLabel *label = new ClickableLabel(label_name);
    QString color = ctx.config->value("color/" + label_name).toString();
    label->setColor(color, color);
    connect(label, SIGNAL(clicked()), m_colorSignalMapper, SLOT(map()));
    m_colorSignalMapper->setMapping(label, label_name);
    m_labels.append(label);

    QLabel *text_label = new QLabel(label_name);
    ui->gridLayout->addWidget(text_label, 0, i);
    ui->gridLayout->addWidget(label, 1, i);
  }
  connect(m_colorSignalMapper, SIGNAL(mapped(const QString&)), this,
      SLOT(openSelector(const QString&)));
}

ColorSettings::~ColorSettings()
{
  delete ui;
}

QColor ColorSettings::openSelector(const QString color_config)
{
  QColorDialog colorSelector;
  QColor color(ctx.config->value("color/" + color_config).toString());
  colorSelector.setCurrentColor(color);
  color = colorSelector.getColor(QColor(0, 255, 0));
  ctx.config->setValue("color/" + color_config, color.name());

  if (color_config == "BG") {
    m_labels.at(N_COLOR)->setColor(color.name(), color.name());
  } else {
    m_labels.at(color_config.toInt() -1)->setColor(color.name(), color.name());
  }
  return color;
}

void ColorSettings::on_buttonBox_accepted()
{
  emit selected();
}
