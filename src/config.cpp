#include "config.h"

Config::Config(QString filename)
    : m_fileName(filename),QSettings(filename,QSettings::IniFormat)
{
;
}

void Config::load_file(QString filename)
{
  m_fileName = filename;
}
