/**
 * @file   parser.h
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

#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>
#include <stdexcept>
#include <vector>

#include <QString>

using std::map;
using std::multimap;
using std::pair;
using std::vector;

class DataStore {
public:
  virtual ~DataStore() {}
  virtual void dump(void) = 0;
};

class Parser {
public:
  Parser(const QString& filename);
  virtual ~Parser();

  virtual DataStore* parse(void) = 0;

protected:
  QString m_fileName;
};

#endif /* __PARSER_H__ */
