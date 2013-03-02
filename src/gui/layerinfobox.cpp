#include "layerinfobox.h"
#include "ui_layerinfobox.h"

#include <QtGui>

#include "context.h"

static const QString bgStyle = \
  "%1 {"
  "  border-style: solid;"
  "  border-width: 2px;"
  "  border-color: black;"
  "  background: %2;"
  "}";

LayerInfoBox::LayerInfoBox(QWidget *parent, const QString& name, QColor color):
    QWidget(parent),
    ui(new Ui::LayerInfoBox),
    m_layer(name), m_color(color), m_checked(false)
{
  ui->setupUi(this);
  ui->layerName->setText(name);
  ui->activeIndicator->setProperty("state", "inactive");
  ui->colorIndicator->setStyleSheet(bgStyle.arg("QLabel", "transparent"));
  ui->layerName->setStyleSheet(bgStyle.arg("QLabel", color.name()));
  item = NULL;
}

LayerInfoBox::~LayerInfoBox()
{
  delete ui;

  if (item) {
    delete item;
  }
}

QString LayerInfoBox::layer(void)
{
  return m_layer;
}

QColor LayerInfoBox::color(void)
{
  return m_color;
}

void LayerInfoBox::setColor(const QColor& color)
{
  m_color = color;
  ui->colorIndicator->setStyleSheet(bgStyle.arg("QLabel", color.name()));

  // Color compensation for composite mode
  int r, g, b;
  QColor bg = ctx.bg_color;
  if (color.lightnessF() > bg.lightnessF()) {
    r = color.red() - bg.red();
    g = color.green() - bg.green();
    b = color.blue() - bg.blue();
  } else {
    r = bg.red() - color.red();
    g = bg.green() - color.green();
    b = bg.blue() - color.blue();
  }
  QColor tc = QColor(abs(r), abs(g), abs(b), 255);

  item->setPen(QPen(tc, 0));
  item->setBrush(tc);
}

void LayerInfoBox::toggle(void)
{
  emit toggled(m_checked);
  m_checked = !m_checked;
  
  if (!m_checked) {
    ui->colorIndicator->setStyleSheet(bgStyle.arg("QLabel", "transparent"));
  }
}

void LayerInfoBox::on_activeIndicator_clicked(void)
{
  ui->activeIndicator->setProperty("state", "active");
  ui->activeIndicator->style()->unpolish(ui->activeIndicator);
  ui->activeIndicator->style()->polish(ui->activeIndicator);
}

void LayerInfoBox::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton) {
    toggle();
  }
}
