/**
 * @file   settingsdialog.h
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

#ifndef __SETTINGSDIALOG_H__
#define __SETTINGSDIALOG_H__

#include <QDialog>
#include <QSignalMapper>
#include <QToolButton>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = 0);
  ~SettingsDialog();

  void accept(void);

public slots:
  void chooseColor(QWidget* widget);
  void on_loadSystemColor_clicked(void);
  void on_loadUserColor_clicked(void);
  void on_saveUserColor_clicked(void);

protected:
  void reloadColorToolButtonColor(void);
  void updateColorToolButtonColor(QToolButton* but);

private:
  Ui::SettingsDialog *ui;
  QSignalMapper* m_sigMapper;
};

#endif // __SETTINGSDIALOG_H__
