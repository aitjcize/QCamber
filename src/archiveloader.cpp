/**
 * @file   archiveloader.cpp
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

#include "archiveloader.h"

#include <QtCore>
#include <QFileInfo>
#include "parser.h"

ArchiveLoader::ArchiveLoader(QString filename): m_fileName(filename)
{
  m_dir = QDir(filename);
}

ArchiveLoader::~ArchiveLoader()
{
}

QString ArchiveLoader::absPath(QString path)
{
  return m_dir.absoluteFilePath(path);
}

QStringList ArchiveLoader::listDir(QString filename)
{
  QDir dir(m_dir.absoluteFilePath(filename));
  return dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
}

QString ArchiveLoader::featuresPath(QString base)
{
  QString plain_path = absPath(base.toLower() + "/features");

  // Ensure feature is not a gzipped file. If so, unzip it.
  QString path = plain_path;
  QFile file(path);

  if (!file.exists()) { // try .[zZ]
    file.setFileName(path + ".Z");

    if (file.exists()) {
      path += ".Z";
    } else {
      file.setFileName(path + ".z");
      if (!file.exists()) {
        return QString();
      }
      path += ".z";
    }

    QStringList args;
    args << "-d" << path;

    int ret = QProcess::execute(GZIP_CMD, args);

    if ((ret == -1) || (ret == -2)) {
      return QString();
    }
  }

  return plain_path;
}
