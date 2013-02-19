#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QSettings>
#include <QStringList>

class Config: public QSettings
{
public:
  Config(QString filename);
  void load_file(QString filename);

private:
  QString m_fileName;
};

#endif // __CONFIG_H__
