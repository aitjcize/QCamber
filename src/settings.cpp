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
