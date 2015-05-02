/**
 * @file   code39.h
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

#ifndef __CODE_39_H__
#define __CODE_39_H__

#include <QChar>
#include <QMap>
#include <QString>

struct code39map {
  QChar tchar;
  QString pattern;
};

class Code39 {
public:
  static void initPatterns(void);
  static QString encode(QString text, bool checksum=false, bool fasc=false);

private:
  static QMap<QChar, QString> s_patterns;
  static QMap<QChar, unsigned> s_checksum;
  static QMap<unsigned, QChar> s_checksum_inv;
  static QMap<QChar, QString> s_fascmap;
};

#endif /* __CODE_39_H__ */
