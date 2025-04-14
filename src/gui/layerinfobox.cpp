/**
 * @file   layerinfobox.cpp
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2012 - 2014 Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "layerinfobox.h"
#include "ui_layerinfobox.h"

#include <QtWidgets>

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
    color = "#FFFFCE";
  } else if (type == "ROUT") {
    color = "#D8D8D8 ";
  }
  ui->layerName->setStyleSheet(bgStyle.arg("QLabel", color));

  m_contextMenu = new QMenu;
  m_contextMenu->addAction(ui->actionFeaturesHistogram);

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
      this, SLOT(showContextMenu(const QPoint&)));
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

bool LayerInfoBox::isActive(void)
{
  return ui->activeIndicator->property("state") == "active";
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

void LayerInfoBox::showContextMenu(const QPoint& point)
{
  m_contextMenu->exec(mapToGlobal(point));
}

void LayerInfoBox::on_activeIndicator_clicked(void)
{
  if (m_checked) {
    bool status = (ui->activeIndicator->property("state") == "active");
    setActive(!status);
  }
}

void LayerInfoBox::on_actionFeaturesHistogram_triggered()
{
  m_featuresHistogramWidget.setTreeViewModel(layer()->reportModel());
  m_featuresHistogramWidget.show();
}

void LayerInfoBox::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton) {
    toggle();
  }
}
