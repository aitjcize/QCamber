#include "viewerwindow.h"
#include "ui_viewerwindow.h"

#include <QtGui>
#include <QDebug>

#include "context.h"
#include "settingsdialog.h"
#include "settings.h"

ViewerWindow::ViewerWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::ViewerWindow)
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

  m_layout = new QVBoxLayout();
  ui->scrollWidget->setLayout(m_layout);

  connect(unitCombo, SIGNAL(currentIndexChanged(int)), this,
      SLOT(unitChanged(int)));

  connect(ui->viewWidget->scene(), SIGNAL(mouseMove(QPointF)), this,
      SLOT(updateCursorCoord(QPointF)));
  connect(ui->viewWidget->scene(), SIGNAL(featureSelected(Symbol*)), this,
      SLOT(updateFeatureDetail(Symbol*)));

  ui->viewWidget->setFocus(Qt::MouseFocusReason);
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

void ViewerWindow::setLayers(const QStringList& layerNames)
{
  ui->viewWidget->clearScene();
  ui->viewWidget->loadProfile(m_step);
  ui->viewWidget->zoomToProfile();

  clearLayout(m_layout, true);
  QString pathTmpl = "steps/%1/layers/%2";

  for(int i = 0; i < layerNames.count(); ++i) {
    LayerSelector *l = new LayerSelector(layerNames[i], m_step, layerNames[i]);

    m_SelectorMap[layerNames[i]] = l;
    connect(l, SIGNAL(Clicked(LayerSelector*, bool)), this,
        SLOT(toggleShowLayer(LayerSelector*, bool)));
    m_layout->addWidget(l);
  }
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
  LayerSelector* selector = m_SelectorMap[name];
  selector->toggle();
}

void ViewerWindow::toggleShowLayer(LayerSelector* selector, bool selected)
{
  if (!selected) {
    if (!selector->item) {
      Layer* layer = new Layer(selector->step(), selector->layer());
      selector->item = layer;
      selector->item->symbolCount();
    }
    selector->setColor(nextColor());
    ui->viewWidget->addItem(selector->item);
    m_actives.append(selector);
    if (m_actives.size() > 1) {
      for (int i = 0; i < m_actives.size(); ++i) {
        m_actives[i]->item->setDoComposite(true);
        m_actives[i]->item->update();
      }
    }
  } else {
    int index = m_colors.indexOf(selector->color());
    m_colorsMap[index] = false;
    ui->viewWidget->removeItem(selector->item);
    selector->item->setDoComposite(false);
    m_actives.removeOne(selector);

    if (m_actives.size() == 1) {
      m_actives[0]->item->setDoComposite(false);
      m_actives[0]->item->update();
    }
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

  for (int i = 0; i < m_actives.size(); ++i) {
    m_actives[i]->setColor(nextColor());
    m_actives[i]->item->update();
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

void ViewerWindow::on_actionAreaZoom_triggered(void)
{
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
  ui->viewWidget->setHighlight(checked);
}

void ViewerWindow::on_actionClearHighlight_triggered(void)
{
  ui->viewWidget->clearHighlight();
}

void ViewerWindow::on_actionShowNotes_toggled(bool checked)
{
  for (int i = 0; i < m_actives.size(); ++i) {
    if (checked) {
      ui->viewWidget->addItem(m_actives[i]->item->notes());
    } else {
      ui->viewWidget->removeItem(m_actives[i]->item->notes());
    }
  }
}
