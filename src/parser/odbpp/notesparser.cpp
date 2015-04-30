/**
 * @file   notesparser.cpp
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

#include "notesparser.h"

#include <QtCore>

void NotesDataStore::putRecord(QStringList args)
{
  m_records.append(new NoteRecord(this, args));
}

const QList<NoteRecord*>& NotesDataStore::records(void)
{
  return m_records;
}

void NotesDataStore::dump(void)
{
}

NotesParser::NotesParser(const QString& filename): Parser(filename)
{
}

NotesParser::~NotesParser()
{
}

NotesDataStore* NotesParser::parse(void)
{
  QFile file(m_fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("parse: can't open `%s' for reading", qPrintable(m_fileName));
    return NULL;
  }

  NotesDataStore* ds = new NotesDataStore;
  while (!file.atEnd()) {
    QString line = file.readLine();
    ds->putRecord(line.split(","));
  }

  return ds;
}
