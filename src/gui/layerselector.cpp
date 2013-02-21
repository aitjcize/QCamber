#include "layerselector.h"
#include "QDebug"
#include "QMenu"
#include "QMouseEvent"

LayerSelector::LayerSelector(const QString& text, const QString& path,
    QWidget *parent)
  :QLabel(text, parent), m_selected(false)
{
  setContextMenuPolicy(Qt::CustomContextMenu);

  m_bgStyleTmpl = "LayerSelector { background-color: %1; color: %2; }";

  m_color = Qt::red;
  m_path = path;
  features = NULL;
}

LayerSelector::~LayerSelector()
{
  if (features) {
    delete features;
  }
}

QColor LayerSelector::color(void)
{
  return m_color;
}

QString LayerSelector::path(void)
{
  return m_path;
}

void LayerSelector::setColor(const QColor& color)
{
  QString tcolor = "black";

  m_color = color;
  m_bgStyle = m_bgStyleTmpl.arg(color.name()).arg(tcolor);
  setStyleSheet(m_bgStyle);
  features->setPen(QPen(m_color, 0));
  features->setBrush(m_color);
}

void LayerSelector::mousePressEvent(QMouseEvent *ev)
{
    if( ev->button() != Qt::LeftButton)
      return;
  if (m_selected) {
    setStyleSheet("QLabel { background-color: transparent; color: black; }");
  }
  emit Clicked(this, m_selected);
  m_selected = !m_selected;
}

void LayerSelector::colorSelector(const QString &color)
{
  QString tcolor = "black";

  m_bgStyle = m_bgStyleTmpl.arg(color).arg(tcolor);
  m_color = QColor(color);

  if (features) {
    features->setPen(QPen(m_color, 0));
    features->setBrush(m_color);
  }

  if (m_selected) {
    setStyleSheet(m_bgStyle);
    emit Clicked(this, m_selected);
    emit Clicked(this, !m_selected);
  }
}
