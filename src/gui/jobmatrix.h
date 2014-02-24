/**
 * @file   jobmatrix.h
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

#ifndef JOBMATRIX_H
#define JOBMATRIX_H

#include <QDialog>
#include <QSignalMapper>
#include <QTableWidget>

#include "structuredtextparser.h"
#include "odbppgraphicsview.h"
#include "clickablelabel.h"
#include "iostream"
#include "viewerwindow.h"

namespace Ui {
  class JobMatrix;
}

class JobMatrix : public QDialog
{
Q_OBJECT

public:
  explicit JobMatrix(QString job, QWidget *parent = 0);
  ~JobMatrix();

  void setMatrix();

private slots:
  void on_CloseButton_clicked();
  void showLayer(QTableWidgetItem *item);
  void drawDrillLine(QString layer_name, int start, int end);
  void selectDrillLine(int);

private:
  Ui::JobMatrix* ui;
  QString m_job;
  QStringList m_stepNames;
  QStringList m_layerNames;
  QStringList m_layerTypes;
  StructuredTextDataStore *m_ds;
};

#endif // JOBMATRIX_H
