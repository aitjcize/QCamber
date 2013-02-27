#include "layerselector.h"

#include <QtGui>

#include "context.h"

LayerSelector::LayerSelector(const QString& text, const QString& step,
    const QString& layer, QWidget *parent)
  :QLabel(text, parent), m_selected(false), m_step(step), m_layer(layer)
{
  setContextMenuPolicy(Qt::CustomContextMenu);

  m_bgStyleTmpl = "LayerSelector { background-color: %1; color: %2; }";

  connect(this,SIGNAL(customContextMenuRequested(QPoint)),
          this,SLOT(showContextmenu(QPoint)));

  m_color = Qt::red;
  item = NULL;

  m_menu = new QMenu(this);
  QAction *featureHistogram = m_menu->addAction("Feature Histogram");

  connect(featureHistogram, SIGNAL(triggered(bool)), this,
      SLOT(showHistogram()));
}

LayerSelector::~LayerSelector()
{
  if (item) {
    delete item;
  }
}

QColor LayerSelector::color(void)
{
  return m_color;
}

QString LayerSelector::step(void)
{
  return m_step;
}

QString LayerSelector::layer(void)
{
  return m_layer;
}

void LayerSelector::setColor(const QColor& color)
{
  QString tcolor = "black";

  m_color = color;
  m_bgStyle = m_bgStyleTmpl.arg(color.name()).arg(tcolor);
  setStyleSheet(m_bgStyle);

  // Color compensation for composite mode
  int r, g, b, a;
  QColor bg = ctx.bg_color;
  if (color.lightnessF() > bg.lightnessF()) {
    r = color.red() - bg.red();
    g = color.green() - bg.green();
    b = color.blue() - bg.blue();
    a = color.alpha() - bg.alpha();
  } else {
    r = bg.red() - color.red();
    g = bg.green() - color.green();
    b = bg.blue() - color.blue();
    a = bg.alpha() - color.alpha();
  }
  QColor tc = QColor(abs(r), abs(g), abs(b), 255);

  item->setPen(QPen(tc, 0));
  item->setBrush(tc);
}

void LayerSelector::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() != Qt::LeftButton)
    return;

  if (m_selected) {
    setStyleSheet("QLabel { background-color: transparent; color: black; }");
  }
  toggle();
}

void LayerSelector::toggle(void)
{
  emit Clicked(this, m_selected);
  m_selected = !m_selected;
}

void LayerSelector::showContextmenu(const QPoint &)
{
  m_menu->exec(QCursor::pos());
}

void LayerSelector::showHistogram()
{
  histogramTable = item->symbolCount();
  histogramTable->show();
}
