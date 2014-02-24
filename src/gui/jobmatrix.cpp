/**
 * @file   jobmatrix.cpp
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

#include "jobmatrix.h"
#include "ui_jobmatrix.h"

#include <QtGui>

#include "context.h"
#include "structuredtextparser.h"

JobMatrix::JobMatrix(QString job, QWidget *parent):
  QDialog(parent), ui(new Ui::JobMatrix), m_job(job)
{
  ui->setupUi(this);

  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  m_ds = parser.parse();

  setMatrix();
}

JobMatrix::~JobMatrix()
{
  delete ui;
  delete m_ds;
}

void JobMatrix::on_CloseButton_clicked()
{
  this->close();
}

void JobMatrix::setMatrix()
{
  StructuredTextDataStore::BlockIterPair ip;
  QString text,start,end;
  int steps, layers;

  steps = layers = 0;
  ip = m_ds->getBlocksByKey("STEP");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    steps++;
  ip = m_ds->getBlocksByKey("LAYER");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    layers++;

  ui->tableWidget->setColumnCount(steps);
  ui->tableWidget->setRowCount(layers);

  steps = 1;
  ip = m_ds->getBlocksByKey("STEP");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    QTableWidgetItem *item = new QTableWidgetItem();
    QString stepName = QString::fromStdString(it->second->get("NAME"))
      .toLower();
    item->setText(stepName);
    m_stepNames.append(stepName);
    ui->tableWidget->setHorizontalHeaderItem(steps - 1,item);

    steps++;
  }

  layers = 0;
  ip = m_ds->getBlocksByKey("LAYER");

  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    QTableWidgetItem *item = new QTableWidgetItem();
    text = QString::fromStdString(it->second->get("TYPE"));
    QString context = QString::fromStdString(it->second->get("CONTEXT"));
    if (context == "MISC") {
      m_layerTypes.append("DOCUMENT");
    } else {
      m_layerTypes.append(text);
    }

    if(text == "SILK_SCREEN")
      text = "(ss ,";
    else if(text == "SOLDER_MASK")
      text = "(sm ,";
    else if(text == "SIGNAL")
      text = "(sig,";
    else if(text == "DRILL")
      text = "(srl,";
    else if(text == "DOCUMENT")
      text = "(doc,";
    else if(text == "ROUT")
      text = "(rt ,";
    else if(text == "SOLDER_PASTE")
      text = "(sp ,";
    else
      text = "( ,";
    if(it->second->get("POLARITY") == "POSITIVE")
      text += "p)  ";
    else
      text += "n)  ";

    QString layerName = QString::fromStdString(it->second->get("NAME"))
      .toLower();
    m_layerNames.append(layerName);
    text += layerName;
    item->setText(text);
    ui->tableWidget->setVerticalHeaderItem(layers, item);

    for(int i = 0; i < m_stepNames.size(); i++)
    {
      text = m_stepNames[i] + "/" + layerName;
      QTableWidgetItem *btn = new QTableWidgetItem(text);
      ui->tableWidget->setItem(layers, i, btn);

      QString pathTmpl = "steps/%1/layers/%2";
      text = pathTmpl.arg(m_stepNames[i]).arg(layerName);

      if (QFile(ctx.loader->featuresPath(text)).size() == 0) {
        btn->setText("");
      }
    }
    layers++;
  }

  ip = m_ds->getBlocksByKey("LAYER");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    text = (QString)it->second->get("TYPE").c_str();
    if(text == "DRILL"){
        start = (QString)it->second->get("START_NAME").c_str();
        end = (QString)it->second->get("END_NAME").c_str();
        if(start != "")
        {
          drawDrillLine((QString)it->second->get("NAME").c_str(),
                        m_layerNames.indexOf(start),m_layerNames.indexOf(end));
        }
    }
  }

  connect(ui->tableWidget->verticalHeader(),SIGNAL(sectionClicked(int)),this,
          SLOT(selectDrillLine(int)));
  connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,
      SLOT(showLayer(QTableWidgetItem *)));
  ui->tableWidget->verticalHeader()->setMovable(true);
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void JobMatrix::showLayer(QTableWidgetItem *item)
{
  if(item->text() == "") return;
  QStringList params = item->text().split("/");
  ViewerWindow* w = new ViewerWindow;
  w->setJob(m_job);
  w->setStep(params[0]);
  w->setLayers(m_layerNames, m_layerTypes);
  w->showLayer(params[1].toLower());
  w->show();
}

void JobMatrix::drawDrillLine(QString layer_name,int start,int end)
{
  int col = ui->tableWidget->columnCount() + 1;
  ui->tableWidget->setColumnCount(col);
  ui->tableWidget->horizontalHeader()->resizeSection(col-1,10);
  ui->tableWidget->setHorizontalHeaderItem(col-1,new QTableWidgetItem(layer_name));
  for(int i = start;i<end+1;i++)
  {
    QTableWidgetItem *line = new QTableWidgetItem(layer_name);
    line->setBackgroundColor(QColor("black"));
    ui->tableWidget->setItem(i,col-1,line);
  }
}

void JobMatrix::selectDrillLine(int index)
{
  int target_col;
  QTableWidgetItem *item;
  for(target_col=m_stepNames.size();
      target_col<ui->tableWidget->columnCount();target_col++)
  {
    if(ui->tableWidget->horizontalHeaderItem(target_col)->text() ==
        ui->tableWidget->verticalHeaderItem(index)->text().split(" ")[2])
      break;
  }

  if(target_col == ui->tableWidget->columnCount()) return;

  for(int col = m_stepNames.size();col < ui->tableWidget->columnCount();col++)
  {
    for(int row = 0;row < m_layerNames.size();row++)
    {
      if (((item = ui->tableWidget->item(row,col)) != 0))
        if(col != target_col)
          item->setBackgroundColor(QColor("black"));
        else
          item->setBackgroundColor(QColor("red"));
    }
  }
}
