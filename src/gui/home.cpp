/**
 * @file   home.cpp
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

#include "home.h"

#include <QtGui>

#include "ui_home.h"
#include "code39.h"
#include "jobmatrix.h"
#include "mainwindow.h"


Context ctx;

extern int yydebug;

Home::Home(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Home)
{
  ui->setupUi(this);
  layout = new QGridLayout;
  layout->setRowMinimumHeight(1,200);
  ui->HomeTable->setLayout(layout);
  ui->HomeTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  ui->HomeTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  showHomePage();
}

Home::~Home()
{
  delete ui;
}


void Home::clearLayout(QLayout* layout, bool deleteWidgets)
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


void Home::showHomePage()
{
  //TODO 找資料夾體下有哪些tar
  clearLayout(ui->HomeTable->layout());
  QString jobName = "demo";
  jobSignalMapper = new QSignalMapper(this);
  ClickableLabel *job = new ClickableLabel(jobName);
  layout->addWidget(job);
  connect(job, SIGNAL(clicked()),jobSignalMapper, SLOT(map()));
  jobSignalMapper->setMapping(job,jobName);
  connect(jobSignalMapper,SIGNAL(mapped (const QString &)), this, SLOT(showJobPage(const QString &)));

}

void Home::showJobPage(const QString jobName)
{
  clearLayout(ui->HomeTable->layout());
  if(jobName != "" && jobName != currJob)
    currJob = jobName;

  Code39::initPatterns();
  yydebug = 0;
  ctx.loader = new ArchiveLoader(currJob+".tgz");
  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  ds = parser.parse();

  ClickableLabel *matrix = new ClickableLabel("Job Matrix");
  connect(matrix,SIGNAL(clicked()),this,SLOT(showMatrix()));
  layout->addWidget(matrix,0,0);

  ClickableLabel *step = new ClickableLabel("Steps");
  connect(step,SIGNAL(clicked()),this,SLOT(showStepPage()));
  layout->addWidget(step,0,1);

  ClickableLabel *custom = new ClickableLabel("Custom Symbol");
  connect(custom,SIGNAL(clicked()),this,SLOT(showCustomSymbolPage()));
  layout->addWidget(custom,0,2);

}

void Home::showMatrix()
{
  matrixptr = new JobMatrix;
  matrixptr->SetMatrix(ds);
  matrixptr->show();
}

void Home::showStepPage()
{
  clearLayout(ui->HomeTable->layout());
  int steps = 0;
  stepSignalMapper = new QSignalMapper(this);

  ClickableLabel *back = new ClickableLabel("Back");
  layout->addWidget(back,0,steps++);
  connect(back,SIGNAL(clicked()),this,SLOT(showJobPage()));

  StructuredTextDataStore::BlockIterPair ip = ds->getBlocksByKey("STEP");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    ClickableLabel *label = new ClickableLabel("this");
    label->setText((QString)it->second->get("NAME").c_str());
    layout->addWidget(label,0,steps++);
    connect(label, SIGNAL(clicked()),stepSignalMapper, SLOT(map()));
    stepSignalMapper->setMapping(label,(QString)it->second->get("NAME").c_str());
  }
  connect(stepSignalMapper,SIGNAL(mapped (const QString &)), this, SLOT(showStep(const QString &)));

}

void Home::showStep(const QString step_name)
{
  stepptr = new MainWindow;

  QStringList layer_name;
  StructuredTextDataStore::BlockIterPair ip = ds->getBlocksByKey("LAYER");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    layer_name.append((QString)it->second->get("NAME").c_str());

  stepptr->setWindowTitle(step_name);
  stepptr->addLayerLabel(&layer_name);
  stepptr->show();
}

void Home::showCustomSymbolPage()
{
  clearLayout(ui->HomeTable->layout());
  symbolSignalMapper = new QSignalMapper(this);
  DIR *dp;
  int i,j;
  struct dirent *dirp;
  if((dp = opendir(ctx.loader->absPath("symbols").toLatin1().data())) == NULL){
    qDebug()<<"Error cant find symbol path";
  }
  i=j=0;
  while((dirp = readdir(dp)) != NULL){
    //dirlist.append(QString(dirp->d_name));
    //qDebug()<<dirlist.back();
    ClickableLabel *label = new ClickableLabel(QString(dirp->d_name));
    layout->addWidget(label,i,j++);
    label->setMinimumSize(55, 0);
    connect(label, SIGNAL(clicked()),symbolSignalMapper, SLOT(map()));
    symbolSignalMapper->setMapping(label,QString(dirp->d_name));
    if(j==5)
    {
      j=0;
      i++;
    }
  }
  connect(symbolSignalMapper,SIGNAL(mapped (const QString &)), this, SLOT(showSymbol(const QString &)));
  closedir(dp);

}

void Home::showSymbol(const QString symbol_name)
{
  stepptr = new MainWindow;
  stepptr->setWindowTitle(symbol_name);
  stepptr->AddCustomSymbol(symbol_name);
  stepptr->show();

}
