/**
 * @file   home.h
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

#ifndef __HOME_H__
#define __HOME_H__

#include <QMainWindow>
#include "clickablelabel.h"
#include <QSignalMapper>
#include "QGridLayout"


#include "archiveloader.h"
#include "structuredtextparser.h"
#include "featuresparser.h"
#include "fontparser.h"
#include "context.h"
#include "gui/jobmatrix.h"
#include "dirent.h"

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit Home(QWidget *parent = 0);
  ~Home();

private slots:
  void showHomePage();
  void showJobPage(const QString jobName = QString());
  void showMatrix();
  void showStep(const QString);
  void showSymbol(const QString);
  void showStepPage();
  void showCustomSymbolPage();

private:
  Ui::Home *ui;
  QSignalMapper *jobSignalMapper,*stepSignalMapper,*symbolSignalMapper;
  void clearLayout(QLayout* , bool deleteWidgets = true);
  QGridLayout *layout;
  JobMatrix *matrixptr;
  MainWindow *stepptr;
  StructuredTextDataStore* ds;
  QString currJob;
};

#endif // __HOME_H__
