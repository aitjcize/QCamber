/**
 * @file   settings.h
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

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <QSettings>
#include <QVariant>

class Settings {
public:
  static Settings* instance();
  static Settings* load(const QString& filename);

  QVariant get(const QString& section, const QString& key);
  void set(const QString& section, const QString& key, const QVariant& value);

private:
  Settings(const QString& filename);

  static Settings* m_Instance;
  QSettings* m_Settings;
};

#define SETTINGS (Settings::instance())

#endif /* __SETTINGS_H__ */
