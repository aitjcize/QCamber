/**
 * @file   jobmanagerdialog.h
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

#ifndef __JOBMANAGERDIALOG_H__
#define __JOBMANAGERDIALOG_H__

#include <QFileSystemModel>
#include <QWidget>

#ifdef Q_WS_WIN
# define TAR_CMD "./tar"
# define GZIP_CMD "./gzip"
# define PATH_SEP ";"
#else
# define TAR_CMD "tar"
# define GZIP_CMD "gzip"
# define PATH_SEP ":"
#endif

namespace Ui {
class JobManagerDialog;
}

class JobManagerDialog : public QWidget
{
  Q_OBJECT
    
public:
  explicit JobManagerDialog(QWidget *parent = 0);
  ~JobManagerDialog();

public slots:
  void on_browseButton_clicked(void);
  void on_importButton_clicked(void);
  void on_removeButton_clicked(void);
  void on_setRootButton_clicked(void);
  void on_listView_doubleClicked(const QModelIndex& index);

private:
  int execute(QString cmd, QStringList args);
  bool recurRemove(const QString& dirname);
    
private:
  Ui::JobManagerDialog *ui;
  QFileSystemModel* m_model;
  QString m_rootDirName;
};

#endif // __JOBMANAGERDIALOG_H__
