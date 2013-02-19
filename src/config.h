#ifndef CONFIG_H
#define CONFIG_H

#include "QSettings"
#include "QStringList"

class Config :public QSettings
{
public:
    Config(QString filename);
    //~Config();

    void load_file(QString filename);
    /*
    void setValue(const QString &key,const QVariant &value)
    {settings->setValue(key,value);}
    QVariant value(const QString &key,const QVariant &value = QVariant())
    {return settings->value(key,value);}
    void beginGroup ( const QString & prefix ){settings->beginGroup(prefix);}
    QStringList childKeys() const {return settings->childKeys();}
    */

private:
    QString m_fileName;
    QSettings *settings;

};

#endif // CONFIG_H
