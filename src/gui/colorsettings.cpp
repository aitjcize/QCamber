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

  for(int i = 1; i < N_COLOR + 2; ++i)
  {
    QString label_name = (i <= N_COLOR)? QString("C%1").arg(i): "BG";

    QString color = ctx.config->value("color/" + label_name).toString();
    ClickableLabel *label = new ClickableLabel(label_name);
    label->setColor(color, color);

    connect(label, SIGNAL(clicked()), m_colorSignalMapper, SLOT(map()));

    m_colorSignalMapper->setMapping(label, i);
    m_labels.append(label);

    QLabel *text_label = new QLabel(label_name);
    ui->gridLayout->addWidget(text_label, 0, i);
    ui->gridLayout->addWidget(label, 1, i);
  }
  connect(m_colorSignalMapper, SIGNAL(mapped(int)), this,
      SLOT(openSelector(int)));
}

ColorSettings::~ColorSettings()
{
  delete ui;
  delete m_colorSignalMapper;
}

QColor ColorSettings::openSelector(int index)
{
  QString name = (index <= N_COLOR)? QString("C%1").arg(index): "BG";
  QColorDialog selector;
  QColor color(ctx.config->value("color/" + name).toString());
  color = selector.getColor(color);
  ctx.config->setValue("color/" + name, color.name());
  m_labels.at(index -1)->setColor(color.name(), color.name());
  return color;
}
