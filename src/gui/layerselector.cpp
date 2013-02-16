#include "layerselector.h"
#include "QDebug"
#include "QMenu"

LayerSelector::LayerSelector(const QString& text, const QString& path,
    QWidget *parent)
  :QLabel(text, parent), m_selected(false)
{
  setContextMenuPolicy(Qt::CustomContextMenu);

  m_bgStyleTmpl = "LayerSelector { background-color: %1; color: %2; }";

  m_color = Qt::red;
  m_path = path;
  features = NULL;

  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
      this, SLOT(show_contextmenu(const QPoint&)));
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

void LayerSelector::slotClicked()
{
  qDebug()<<"QQ";
}

void LayerSelector::mouseDoubleClickEvent(QMouseEvent *)
{
  if (m_selected) {
    setStyleSheet("QLabel { background-color: transparent; color: black; }");
  }
  emit doubleClicked(this, m_selected);
  m_selected = !m_selected;
}

void LayerSelector::show_contextmenu(const QPoint &point)
{
  QMenu *cmenu = new QMenu();
  m_colorSignalMapper = new QSignalMapper(this);
  QAction *ascendSortAction;

  ascendSortAction = cmenu->addAction("cyan");
  connect(ascendSortAction, SIGNAL(triggered(bool)), m_colorSignalMapper,
      SLOT(map()));
  m_colorSignalMapper->setMapping(ascendSortAction,"cyan");

  ascendSortAction = cmenu->addAction("red");
  connect(ascendSortAction, SIGNAL(triggered(bool)), m_colorSignalMapper,
      SLOT(map()));
  m_colorSignalMapper->setMapping(ascendSortAction,"red");

  ascendSortAction = cmenu->addAction("magenta");
  connect(ascendSortAction, SIGNAL(triggered(bool)), m_colorSignalMapper,
      SLOT(map()));
  m_colorSignalMapper->setMapping(ascendSortAction,"magenta");

  ascendSortAction = cmenu->addAction("green");
  connect(ascendSortAction, SIGNAL(triggered(bool)), m_colorSignalMapper,
      SLOT(map()));
  m_colorSignalMapper->setMapping(ascendSortAction,"green");

  ascendSortAction = cmenu->addAction("yellow");
  connect(ascendSortAction, SIGNAL(triggered(bool)), m_colorSignalMapper,
      SLOT(map()));
  m_colorSignalMapper->setMapping(ascendSortAction,"yellow");

  ascendSortAction = cmenu->addAction("blue");
  connect(ascendSortAction, SIGNAL(triggered(bool)), m_colorSignalMapper,
      SLOT(map()));
  m_colorSignalMapper->setMapping(ascendSortAction,"blue");


  connect(m_colorSignalMapper, SIGNAL(mapped (const QString &)), this,
      SLOT(colorSelector(const QString &)));
  cmenu->exec(QCursor::pos());
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
    emit doubleClicked(this, m_selected);
    emit doubleClicked(this, !m_selected);
  }
}
