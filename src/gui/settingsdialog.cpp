/**
 * @file   settingsdialog.cpp
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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QtGui>

#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
  ui->setupUi(this);

  m_sigMapper = new QSignalMapper;;

#define MAP(mapper, name) \
  (mapper)->setMapping(ui->name, ui->name); \
  connect(ui->name, SIGNAL(clicked()), mapper, SLOT(map()));

  MAP(m_sigMapper, colorBG);
  MAP(m_sigMapper, colorC1);
  MAP(m_sigMapper, colorC2);
  MAP(m_sigMapper, colorC3);
  MAP(m_sigMapper, colorC4);
  MAP(m_sigMapper, colorC5);
  MAP(m_sigMapper, colorC6);
#undef MAP

  reloadColorToolButtonColor();

  connect(m_sigMapper, SIGNAL(mapped(QWidget*)),
      this, SLOT(chooseColor(QWidget*)));
}

SettingsDialog::~SettingsDialog()
{
  delete ui;
}

void SettingsDialog::accept(void)
{
  hide();
}

void SettingsDialog::on_loadSystemColor_clicked(void)
{
  QStringList names, colors;
  names << "BG" << "C1" << "C2" << "C3" << "C4" << "C5" << "C6";
  colors << "#000000" << "#ff0000" << "#4ba503" << "#00adc6" << "#ffff3e"
    << "#00007f" << "#aa00ff";

  for (int i = 0; i < names.size(); ++i)  {
    SETTINGS->set("Color", names[i], colors[i]);
  }

  reloadColorToolButtonColor();
}

void SettingsDialog::on_loadUserColor_clicked(void)
{
  if (SETTINGS->get("Color", "UC1") == QVariant()) {
    on_loadSystemColor_clicked();
  }

  QStringList names;
  names << "BG" << "C1" << "C2" << "C3" << "C4" << "C5" << "C6";

  for (int i = 0; i < names.size(); ++i)  {
    QString ucolor = SETTINGS->get("Color", "U" + names[i]).toString();
    SETTINGS->set("Color", names[i], ucolor);
  }

  reloadColorToolButtonColor();
}

void SettingsDialog::on_saveUserColor_clicked(void)
{
  QStringList names;
  names << "BG" << "C1" << "C2" << "C3" << "C4" << "C5" << "C6";

  for (int i = 0; i < names.size(); ++i)  {
    QString color = SETTINGS->get("Color", names[i]).toString();
    SETTINGS->set("Color", "U" + names[i], color);
  }
}

void SettingsDialog::reloadColorToolButtonColor(void)
{
  updateColorToolButtonColor(ui->colorBG);
  updateColorToolButtonColor(ui->colorC1);
  updateColorToolButtonColor(ui->colorC2);
  updateColorToolButtonColor(ui->colorC3);
  updateColorToolButtonColor(ui->colorC4);
  updateColorToolButtonColor(ui->colorC5);
  updateColorToolButtonColor(ui->colorC6);
}

void SettingsDialog::updateColorToolButtonColor(QToolButton* but)
{
  QString tmpl("QToolButton { background-color: %1; color: %2; }");
  QColor fg(SETTINGS->get("Color", but->text()).toString());
  QColor bg(255 - fg.red(), 255 - fg.green(), 255 - fg.blue(), 25);
  but->setStyleSheet(tmpl.arg(fg.name()).arg(bg.name()));
}

void SettingsDialog::chooseColor(QWidget* widget)
{
  QToolButton* but = qobject_cast<QToolButton*>(widget);
  QString colorName = but->text();
  QColorDialog selector;
  QColor color(SETTINGS->get("Color", colorName).toString());
  color = selector.getColor(color);
  if (color.isValid()) {
    SETTINGS->set("Color", colorName, color.name());
    updateColorToolButtonColor(but);
  }
}
