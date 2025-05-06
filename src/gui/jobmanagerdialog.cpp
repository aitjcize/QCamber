/**
 * @file   jobmanagerdialog.cpp
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

#include "jobmanagerdialog.h"
#include "ui_jobmanagerdialog.h"

#include <QtWidgets>

#include "context.h"
#include "jobmatrix.h"
#include "settings.h"
#include "structuredtextparser.h"

JobManagerDialog::JobManagerDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JobManagerDialog)
{
  ui->setupUi(this);

  m_rootDirName = SETTINGS->get("System", "RootDir").toString();

  if (m_rootDirName.isEmpty()) {
    m_rootDirName = QCoreApplication::applicationDirPath() + "/Jobs";
    SETTINGS->set("System", "RootDir", m_rootDirName);
  }

  QDir jobsDir(m_rootDirName);
  if (!jobsDir.exists()) {
    QDir::root().mkdir(m_rootDirName);
  }

  m_model = new QFileSystemModel;
  m_model->setRootPath(m_rootDirName);

  ui->listView->setModel(m_model);
  ui->listView->setRootIndex(m_model->index(m_rootDirName));
}

JobManagerDialog::~JobManagerDialog()
{
  delete ui;
  delete m_model;
}

void JobManagerDialog::on_browseButton_clicked(void)
{
  QFileDialog diag(NULL, "Choose a tarball", "",
      "ODB++ database (*.tgz *.tar.gz)");
  diag.exec();

  QString sel = diag.selectedFiles()[0];
  if (sel.endsWith(".tgz") || sel.endsWith(".tar.gz")) {
    ui->filenameLineEdit->setText(sel);
  }
}

void JobManagerDialog::on_importButton_clicked(void)
{
  QString filename = ui->filenameLineEdit->text();

  if (filename.isEmpty()) {
    QMessageBox::critical(this, "Error", "No filename specified!");
    return;
  }

  QString jobName =  QFileInfo(filename).baseName();

  QDir jobsDir(m_rootDirName);
  if (!jobsDir.mkdir(jobName)) {
    QMessageBox::critical(this, "Error", "Job with same name exists!");
    return;
  }

  QString extractDir = jobsDir.absoluteFilePath(jobName);

  // Decompress tarball
  QStringList args;

#ifdef Q_WS_WIN
  filename.replace(":", "");
  filename.prepend('/');
#endif

  args << "xf" << filename << "--strip-components=1" << "-C" << extractDir;

  QMessageBox msg(QMessageBox::Information, "Progress",
      "Decompressing archive...");
  msg.setStandardButtons(QMessageBox::NoButton);
  msg.show();

  int ret = execute(TAR_CMD, args);

  msg.hide();

  if (ret != 0) {
    QMessageBox::critical(this, "Error",
        QString("Error when decompressing `%1'").arg(filename));
    recurRemove(extractDir);
    return;
  }

  // Decompress all layers
  msg.setText("Decompressing all layers...");
  msg.show();

  QString matrix = extractDir + "/matrix/matrix";

  StructuredTextParser parser(matrix);
  StructuredTextDataStore* ds = parser.parse();

  if (ds == NULL) {
    QMessageBox::critical(this, "Error",
        QString("`%1' is not a valid ODB++ database.").arg(filename));
    recurRemove(extractDir);
    return;
  }

  StructuredTextDataStore::BlockIterPair ip;
  QStringList steps, layers;

  ip = ds->getBlocksByKey("STEP");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    steps.append(QString::fromStdString(it->second->get("NAME")).toLower());
  }

  ip = ds->getBlocksByKey("LAYER");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    layers.append(QString::fromStdString(it->second->get("NAME")).toLower());
  }

  QString layerPathTmpl = extractDir + "/steps/%1/layers/%2/features";
  for (int i = 0; i < steps.size(); ++i) {
    for (int j = 0; j < layers.size(); ++j) {
      QString path = layerPathTmpl.arg(steps[i]).arg(layers[j]);
      QString gzFilename;
      if (QFile(path + ".Z").exists()) {
        gzFilename = path + ".Z";
      } else if (QFile(path + ".z").exists()) {
        gzFilename = path + ".z";
      } else {
        continue;
      }

      msg.setText(QString("Decompressing %1/%2 ...")
          .arg(steps[i]).arg(layers[j]));

      QStringList args;
      args << "-d" << gzFilename;

      int ret = execute(GZIP_CMD, args);

      if (ret != 0) {
        QMessageBox::critical(this, "Error",
            QString("Error when decompressing `%1'").arg(gzFilename));
        recurRemove(extractDir);
        break;
      }
    }
  }

  msg.hide();
}


void JobManagerDialog::on_removeButton_clicked(void)
{
  QString name = m_model->data(ui->listView->currentIndex()).toString();

  int ret = QMessageBox::question(this,"Confirm",
      QString("Are you sure you want to remove `%1'").arg(name),
        QMessageBox::Yes, QMessageBox::No);

  if (ret != QMessageBox::Yes)
    return;

  recurRemove(m_rootDirName + "/" + name);
}

void JobManagerDialog::on_setRootButton_clicked(void)
{
  QFileDialog diag(NULL, "Choose a directory", m_rootDirName);
  diag.setFileMode(QFileDialog::Directory);
  diag.setOption(QFileDialog::ShowDirsOnly);

  if (diag.exec()) {
    m_rootDirName = diag.selectedFiles()[0];
    SETTINGS->set("System", "RootDir", m_rootDirName);

    m_model->setRootPath(m_rootDirName);
    ui->listView->setModel(m_model);
    ui->listView->setRootIndex(m_model->index(m_rootDirName));
  }
}

void JobManagerDialog::on_listView_doubleClicked(const QModelIndex& index)
{
  QString name = m_model->data(index).toString();
  ctx.loader = new ArchiveLoader(m_rootDirName + "/" + name);

  JobMatrix* job = new JobMatrix(name);
  job->show();
  hide();
}

int JobManagerDialog::execute(QString cmd, QStringList args)
{
  QEventLoop loop;

  QProcess process;
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  env.insert("PATH", env.value("PATH") +
      PATH_SEP + QCoreApplication::applicationDirPath());
  process.setProcessEnvironment(env);
  connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)),
      &loop, SLOT(quit()));

  process.start(cmd, args);
  loop.exec();

  return process.exitCode();
}

bool JobManagerDialog::recurRemove(const QString& dirname)
{
  bool result = true;
  QDir dir(dirname);

  if (dir.exists(dirname)) {
    Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot |
          QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files,
          QDir::DirsFirst)) {
      if (info.isDir()) {
        result = recurRemove(info.absoluteFilePath());
      }
      else {
        result = QFile::remove(info.absoluteFilePath());
      }

      if (!result) {
        return result;
      }
    }
    result = dir.rmdir(dirname);
  }
  return result;
}
