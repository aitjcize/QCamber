/**
 * @file   notes.cpp
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

#include "notes.h"

#include <QtWidgets>

#include "context.h"
#include "notesparser.h"

Notes::Notes(QString step, QString layer): Symbol("symbol"), m_empty(false)
{
  QString filename = ctx.loader->absPath(QString("steps/%1/layers/%2/notes")
      .arg(step).arg(layer));

  NotesParser parser(filename);
  NotesDataStore* ds = parser.parse();
  if (!ds) {
    m_empty = true;
    return;
  }

  QList<NoteRecord*> records = ds->records();
  for (QList<NoteRecord*>::const_iterator it = ds->records().begin();
      it != ds->records().end(); ++it) {
    addChild((*it)->createSymbol());
  }
}

Notes::~Notes()
{
}

bool Notes::empty(void)
{
  return m_empty;
}
