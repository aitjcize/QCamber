#include "viewerwindow.h"
#include "ui_viewerwindow.h"

#include <QtGui>
#include <QDebug>

#include "context.h"
#include "layerinfobox.h"
#include "settingsdialog.h"
#include "settings.h"

ViewerWindow::ViewerWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::ViewerWindow), m_activeInfoBox(NULL),
  m_transition(false)
{
  ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);

  loadColorConfig();

  m_cursorCoordLabel = new QLabel();
  m_featureDetailLabel = new QLabel();
  m_featureDetailLabel->setAlignment(Qt::AlignVCenter);
  m_cursorCoordLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
  statusBar()->addPermanentWidget(m_featureDetailLabel);
  statusBar()->addPermanentWidget(m_cursorCoordLabel, 1);

  QComboBox* unitCombo = new QComboBox;
  unitCombo->addItem("Inch");
  unitCombo->addItem("MM");
  statusBar()->addPermanentWidget(unitCombo);

  connect(unitCombo, SIGNAL(currentIndexChanged(int)), this,
      SLOT(unitChanged(int)));

  connect(ui->viewWidget->scene(), SIGNAL(mouseMove(QPointF)), this,
      SLOT(updateCursorCoord(QPointF)));
  connect(ui->viewWidget->scene(), SIGNAL(featureSelected(Symbol*)), this,
      SLOT(updateFeatureDetail(Symbol*)));

  ui->viewWidget->setFocus(Qt::MouseFocusReason);
  ui->actionAreaZoom->setChecked(true);
}

ViewerWindow::~ViewerWindow()
{
  delete ui;
}

void ViewerWindow::setStep(QString step)
{
  setWindowTitle(step);
  m_step = step;
}

void ViewerWindow::setLayers(const QStringList& layers,
    const QStringList& types)
{
  ui->viewWidget->clearScene();
  ui->viewWidget->loadProfile(m_step);

  QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollWidget->layout());
  clearLayout(layout, true);
  QString pathTmpl = "steps/%1/layers/%2";

  for (int i = 0; i < layers.count(); ++i) {
    LayerInfoBox *l = new LayerInfoBox(layers[i], m_step, types[i]);

    connect(l, SIGNAL(toggled(bool)), this, SLOT(toggleShowLayer(bool)));
    connect(l, SIGNAL(activated(bool)), this, SLOT(layerActivated(bool)));

    m_SelectorMap[layers[i]] = l;
    layout->addWidget(l);
  }
  layout->addStretch();
}

void ViewerWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
  while (QLayoutItem* item = layout->takeAt(0))
  {
    if (deleteWidgets)
    {
      if (QWidget* widget = item->widget())
        delete widget;
    }
    else if (QLayout* childLayout = item->layout())
      clearLayout(childLayout, deleteWidgets);
    delete item;
  }
}

void ViewerWindow::showLayer(QString name)
{
  LayerInfoBox* infobox = m_SelectorMap[name];
  infobox->toggle();
}

void ViewerWindow::show(void)
{
  QMainWindow::show();
  ui->viewWidget->initialZoom();
}

void ViewerWindow::toggleShowLayer(bool selected)
{
  LayerInfoBox* infobox = dynamic_cast<LayerInfoBox*>(sender());
  if (!selected) {
    ui->viewWidget->addLayer(infobox->layer());
    infobox->setColor(nextColor());

    m_visibles.append(infobox);
    if (m_visibles.size() == 1) {
      infobox->setActive(true);
    } else {
      for (int i = 0; i < m_visibles.size(); ++i) {
        m_visibles[i]->layer()->forceUpdate();
      }
    }
  } else {
    int index = m_colors.indexOf(infobox->color());
    m_colorsMap[index] = false;
    ui->viewWidget->removeItem(infobox->layer());
    m_visibles.removeOne(infobox);

    if (infobox->isActive()) {
      if (m_visibles.size()) {
        m_visibles.last()->setActive(true);
      }
    }
  }
}

void ViewerWindow::layerActivated(bool status)
{
  LayerInfoBox* infobox = dynamic_cast<LayerInfoBox*>(sender());
  if (status) {
    if (m_activeInfoBox && m_activeInfoBox != infobox) {
      m_activeInfoBox->setActive(false);
    }
    m_activeInfoBox = infobox;
    if (ui->actionHighlight->isChecked()) {
      m_activeInfoBox->layer()->setHighlight(true);
    }
  } else {
    infobox->layer()->setHighlight(false);
  }
}

QColor ViewerWindow::nextColor(void)
{
  for (int i = 0; i < m_colors.size(); ++i) {
    if (!m_colorsMap[i]) {
      m_colorsMap[i] = true;
      return m_colors[i];
    }
  }
  return Qt::red;
}

void ViewerWindow::loadColorConfig()
{
  ctx.bg_color = QColor(SETTINGS->get("color", "BG").toString());
  ui->viewWidget->setBackgroundColor(ctx.bg_color);

  m_colors.clear();
  for(int i = 0; i < 6; ++i) {
    m_colors << QColor(SETTINGS->get("Color",
          QString("C%1").arg(i + 1)).toString());
  }

  for (int i = 0; i < m_colors.size(); ++i) {
    m_colorsMap[i] = false;
  }

  for (int i = 0; i < m_visibles.size(); ++i) {
    m_visibles[i]->setColor(nextColor());
    m_visibles[i]->layer()->forceUpdate();
  }
}

void ViewerWindow::unitChanged(int index)
{
  m_displayUnit = (DisplayUnit)index;
}

void ViewerWindow::updateCursorCoord(QPointF pos)
{
  QString text;
  if (m_displayUnit == U_INCH) {
    text.sprintf("(%f, %f)", pos.x(), -pos.y());
  } else {
    text.sprintf("(%f, %f)", pos.x() * 25.4, -pos.y() * 25.4);
  }
  m_cursorCoordLabel->setText(text);
}

void ViewerWindow::updateFeatureDetail(Symbol* symbol)
{
  m_featureDetailLabel->setText(symbol->infoText());
}

void ViewerWindow::on_actionSetColor_triggered(void)
{
  SettingsDialog dialog;
  dialog.exec();
  loadColorConfig();
}

void ViewerWindow::on_actionZoomIn_triggered(void)
{
  ui->viewWidget->scaleView(2);
}

void ViewerWindow::on_actionZoomOut_triggered(void)
{
  ui->viewWidget->scaleView(0.5);
}

void ViewerWindow::on_actionHome_triggered(void)
{
  ui->viewWidget->zoomToProfile();
}

void ViewerWindow::on_actionMousePan_toggled(bool checked)
{
  Q_UNUSED(checked);
  if (m_transition) {
    return;
  }
  m_transition = true;
  ui->actionAreaZoom->setChecked(false);
  ui->actionHighlight->setChecked(false);
  m_transition = false;
  ui->viewWidget->setZoomMode(ODBPPGraphicsView::MousePan);
}

void ViewerWindow::on_actionAreaZoom_toggled(bool checked)
{
  Q_UNUSED(checked);
  if (m_transition) {
    return;
  }
  m_transition = true;
  ui->actionMousePan->setChecked(false);
  ui->actionHighlight->setChecked(false);
  m_transition = false;
  ui->viewWidget->setZoomMode(ODBPPGraphicsView::AreaZoom);
}

void ViewerWindow::on_actionPanLeft_triggered(void)
{
  ui->viewWidget->scrollView(-100, 0);
}

void ViewerWindow::on_actionPanRight_triggered(void)
{
  ui->viewWidget->scrollView(100, 0);
}

void ViewerWindow::on_actionPanUp_triggered(void)
{
  ui->viewWidget->scrollView(0, -100);
}

void ViewerWindow::on_actionPanDown_triggered(void)
{
  ui->viewWidget->scrollView(0, 100);
}

void ViewerWindow::on_actionHighlight_toggled(bool checked)
{
  if (m_transition) {
    return;
  }
  m_transition = true;
  ui->actionAreaZoom->setChecked(false);
  ui->actionMousePan->setChecked(false);
  m_transition = false;
  ui->viewWidget->setHighlight(checked);
  if (m_activeInfoBox) {
    m_activeInfoBox->layer()->setHighlight(checked);
  }
}

void ViewerWindow::on_actionClearHighlight_triggered(void)
{
  ui->viewWidget->clearHighlight();
}

void ViewerWindow::on_actionShowNotes_toggled(bool checked)
{
  for (int i = 0; i < m_visibles.size(); ++i) {
    if (checked) {
      ui->viewWidget->addItem(m_visibles[i]->layer()->notes());
    } else {
      ui->viewWidget->removeItem(m_visibles[i]->layer()->notes());
    }
  }
}
