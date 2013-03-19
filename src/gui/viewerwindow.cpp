#include "viewerwindow.h"
#include "ui_viewerwindow.h"

#include <QtGui>
#include <QDebug>

#include "context.h"
#include "layerinfobox.h"
#include "settingsdialog.h"
#include "settings.h"

ViewerWindow::ViewerWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::ViewerWindow), m_displayUnit(U_INCH),
  m_activeInfoBox(NULL), m_transition(false)
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

  m_featurePropertiesDialog = new FeaturePropertiesDialog(this);

  connect(unitCombo, SIGNAL(currentIndexChanged(int)), this,
      SLOT(unitChanged(int)));

  connect(ui->viewWidget->scene(), SIGNAL(mouseMove(QPointF)), this,
      SLOT(updateCursorCoord(QPointF)));
  connect(ui->viewWidget->scene(), SIGNAL(measureRectSelected(QRectF)), this,
      SLOT(updateMeasureResult(QRectF)));
  connect(ui->viewWidget->scene(), SIGNAL(featureSelected(Symbol*)), this,
      SLOT(updateFeatureDetail(Symbol*)));
  connect(ui->viewWidget->scene(), SIGNAL(featureSelected(Symbol*)),
      m_featurePropertiesDialog, SLOT(update(Symbol*)));

  connect(ui->miniMapView, SIGNAL(minimapRectSelected(QRectF)), ui->viewWidget,
      SLOT(zoomToRect(QRectF)));
  connect(ui->viewWidget, SIGNAL(sceneRectChanged(QRectF)), ui->miniMapView,
      SLOT(redrawSceneRect(QRectF)));

  // bgColorChanged signal
  connect(this, SIGNAL(bgColorChanged(QColor)), ui->viewWidget,
      SLOT(setBackgroundColor(QColor)));
  connect(this, SIGNAL(bgColorChanged(QColor)), ui->miniMapView,
      SLOT(setBackgroundColor(QColor)));

  ui->viewWidget->setFocus(Qt::MouseFocusReason);
  ui->actionAreaZoom->setChecked(true);
}

ViewerWindow::~ViewerWindow()
{
  delete ui;
  delete m_featurePropertiesDialog;
}

void ViewerWindow::setJob(QString job)
{
  m_job = job;
}

void ViewerWindow::setStep(QString step)
{
  m_step = step;
  setWindowTitle(QString("CAMViewer::%1::%2").arg(m_job).arg(m_step));
}

void ViewerWindow::setLayers(const QStringList& layers,
    const QStringList& types)
{
  ui->viewWidget->clearScene();
  ui->viewWidget->loadProfile(m_step);
  ui->miniMapView->loadProfile(m_step);

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
  ui->miniMapView->zoomToAll();
}

void ViewerWindow::toggleShowLayer(bool selected)
{
  LayerInfoBox* infobox = dynamic_cast<LayerInfoBox*>(sender());
  if (!selected) {
    ui->viewWidget->addLayer(infobox->layer());
    infobox->setColor(nextColor());
    infobox->layer()->setShowOutline(ui->actionShowOutline->isChecked());
    infobox->layer()->setShowStepRepeat(ui->actionShowStepRepeat->isChecked());

    m_visibles.append(infobox);
    if (m_visibles.size() == 1) {
      infobox->setActive(true);
    }
  } else {
    int index = m_colors.indexOf(infobox->color());
    m_colorsMap[index] = false;
    ui->viewWidget->removeLayer(infobox->layer());
    m_visibles.removeOne(infobox);

    if (infobox->isActive()) {
      if (m_visibles.size()) {
        m_visibles.last()->setActive(true);
      }
    }
  }
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
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
      m_activeInfoBox->layer()->setHighlightEnabled(true);
    }
  } else {
    infobox->layer()->setHighlightEnabled(false);
  }
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
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

  emit bgColorChanged(ctx.bg_color);
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

void ViewerWindow::updateMeasureResult(QRectF rect)
{
  QString result("DX=%1, DY=%2, D=%3");
  m_featureDetailLabel->setText(result.arg(rect.width()).arg(rect.height())
    .arg(qSqrt(rect.width() * rect.width() + rect.height() * rect.height())));
}

void ViewerWindow::on_actionSetColor_triggered(void)
{
  SettingsDialog dialog;
  dialog.exec();
  loadColorConfig();
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionZoomIn_triggered(void)
{
  ui->viewWidget->scaleView(2);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionZoomOut_triggered(void)
{
  ui->viewWidget->scaleView(0.5);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionHome_triggered(void)
{
  ui->viewWidget->zoomToAll();
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
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
  ui->actionMeasure->setChecked(false);
  m_transition = false;
  ui->viewWidget->setZoomMode(ODBPPGraphicsView::MousePan);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
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
  ui->actionMeasure->setChecked(false);
  m_transition = false;
  ui->viewWidget->setZoomMode(ODBPPGraphicsView::AreaZoom);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionPanLeft_triggered(void)
{
  ui->viewWidget->scrollView(-500, 0);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionPanRight_triggered(void)
{
  ui->viewWidget->scrollView(500, 0);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionPanUp_triggered(void)
{
  ui->viewWidget->scrollView(0, -500);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionPanDown_triggered(void)
{
  ui->viewWidget->scrollView(0, 500);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionHighlight_toggled(bool checked)
{
  if (m_transition) {
    return;
  }
  m_transition = true;
  ui->actionAreaZoom->setChecked(false);
  ui->actionMousePan->setChecked(false);
  ui->actionMeasure->setChecked(false);
  m_transition = false;
  ui->viewWidget->setHighlightEnabled(checked);
  if (m_activeInfoBox) {
    m_activeInfoBox->layer()->setHighlightEnabled(checked);
  }
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionClearHighlight_triggered(void)
{
  ui->viewWidget->clearHighlight();
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionFeatureProperties_triggered(void)
{
  m_featurePropertiesDialog->show();
}

void ViewerWindow::on_actionMeasure_toggled(bool checked)
{
  if (m_transition) {
    return;
  }
  m_transition = true;
  ui->actionAreaZoom->setChecked(false);
  ui->actionMousePan->setChecked(false);
  ui->actionHighlight->setChecked(false);
  m_transition = false;

  ui->viewWidget->setMeasureEnabled(checked);
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionShowOutline_toggled(bool checked)
{
  for (int i = 0; i < m_visibles.size(); ++i) {
    m_visibles[i]->layer()->setShowOutline(checked);
  }
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}

void ViewerWindow::on_actionShowStepRepeat_toggled(bool checked)
{
  for (int i = 0; i < m_visibles.size(); ++i) {
    m_visibles[i]->layer()->setShowStepRepeat(checked);
  }
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
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
  ui->viewWidget->setFocus(Qt::MouseFocusReason);
}
