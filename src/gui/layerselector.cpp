#include "layerselector.h"

#include <QtGui>

LayerSelector::LayerSelector(const QString& text, const QString& step,
    const QString& layer, QWidget *parent)
  :QLabel(text, parent), m_step(step), m_layer(layer), m_selected(false)
{
  setContextMenuPolicy(Qt::CustomContextMenu);

  m_bgStyleTmpl = "LayerSelector { background-color: %1; color: %2; }";

  m_color = Qt::red;
  item = NULL;
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
  item->setPen(QPen(m_color, 0));
  item->setBrush(m_color);
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
