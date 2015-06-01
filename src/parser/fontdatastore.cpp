/**
 * @file   fontdatastore.cpp
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

#include "fontdatastore.h"

void FontDataStore::putXSize(qreal xsize)
{
  m_xsize = xsize;
}

void FontDataStore::putYSize(qreal ysize)
{
  m_ysize = ysize;
}

void FontDataStore::putOffset(qreal offset)
{
  m_offset = offset;
}

void FontDataStore::putCharRecord(CharRecord* rec)
{
  m_records[rec->tchar] = rec;
}

qreal FontDataStore::offset(void)
{
  return m_offset;
}

qreal FontDataStore::xsize(void)
{
  return m_xsize;
}

qreal FontDataStore::ysize(void)
{
  return m_ysize;
}

CharRecord* FontDataStore::charRecord(const char tchar)
{
  return m_records[tchar];
}

void FontDataStore::dump(void)
{
}

