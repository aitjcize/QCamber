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

LayerInfoBox::LayerInfoBox(const QString& name, const QString& step,
    const QString& type):
    QWidget(NULL),
    ui(new Ui::LayerInfoBox),
    m_name(name), m_step(step), m_layer(NULL), m_checked(false)
{
  ui->setupUi(this);
  ui->layerName->setText(name);
  ui->activeIndicator->setProperty("state", "inactive");
  ui->colorIndicator->setStyleSheet(bgStyle.arg("QLabel", "transparent"));

  QString color;
  if (type == "SILK_SCREEN") {
    color = "#FFFFFF";
  } else if (type == "SOLDER_MASK") {
    color = "#00A57C";
  } else if (type == "SIGNAL") {
    color = "#FCC64D";
  } else if (type == "DRILL") {
    color = "#9BB4BF";
  } else if (type == "DOCUMENT") {
    color = "#9BDBDB";
  } else if (type == "SOLDER_PASTE") {
    color = "#9BDBDB";
  } else if (type == "ROUT") {
    color = "#D8D8D8 ";
  }
  ui->layerName->setStyleSheet(bgStyle.arg("QLabel", color));
}

LayerInfoBox::~LayerInfoBox()
{
  delete ui;

  if (m_layer) {
    delete m_layer;
  }
}

QString LayerInfoBox::name(void)
{
  return m_name;
}

QColor LayerInfoBox::color(void)
{
  return m_color;
}

Layer* LayerInfoBox::layer(void)
{
  if (!m_layer) {
    m_layer = new Layer(m_step, m_name);
  }
  return m_layer;
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

  if (m_layer) {
    m_layer->setPen(QPen(tc, 0));
    m_layer->setBrush(tc);
  }
}

void LayerInfoBox::setActive(bool status)
{
  ui->activeIndicator->setProperty("state", (status? "active": "inactive"));
  ui->activeIndicator->style()->unpolish(ui->activeIndicator);
  ui->activeIndicator->style()->polish(ui->activeIndicator);
  emit activated(status);
}

void LayerInfoBox::toggle(void)
{
  emit toggled(m_checked);
  m_checked = !m_checked;
  
  if (!m_checked) {
    ui->colorIndicator->setStyleSheet(bgStyle.arg("QLabel", "transparent"));
    setActive(false);
  }
}

void LayerInfoBox::on_activeIndicator_clicked(void)
{
  if (m_checked) {
    bool status = (ui->activeIndicator->property("state") == "active");
    setActive(!status);
  }
}

void LayerInfoBox::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton) {
    toggle();
  }
}
