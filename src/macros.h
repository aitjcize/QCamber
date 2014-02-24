/**
 * @file   macros.h
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

#ifndef __MACROS_H__
#define __MACROS_H__

#define R2D (180.0 / M_PI)
#define D2R (M_PI / 180.0)

#define APPEND_ROW(root, header, data)                                      \
  ({                                                                        \
    QList<QStandardItem*> c;                                                \
    QStandardItem* item = new QStandardItem(header);                        \
    c.append(item);                                                         \
    c.append(new QStandardItem(data));                                      \
    root->appendRow(c);                                                     \
    item;                                                                   \
  })

#endif /* __MACROS_H__ */
