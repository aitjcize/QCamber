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
