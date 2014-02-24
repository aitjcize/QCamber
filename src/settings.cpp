/**
 * @file   settings.cpp
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

#include "settings.h"

Settings* Settings::m_Instance = NULL;

Settings* Settings::instance()
{
  return m_Instance;
}

Settings* Settings::load(const QString& filename)
{
  m_Instance = new Settings(filename);
  return m_Instance;
}

Settings::Settings(const QString& filename)
{
  m_Settings = new QSettings(filename, QSettings::IniFormat);
}

QVariant Settings::get(const QString& section, const QString& key)
{
  m_Settings->beginGroup(section);
  QVariant value = m_Settings->value(key);
  m_Settings->endGroup();
  return value;
}

void Settings::set(const QString& section, const QString& key,
    const QVariant& value)
{
  m_Settings->beginGroup(section);
  m_Settings->setValue(key, value);
  m_Settings->endGroup();
  m_Settings->sync();
}
