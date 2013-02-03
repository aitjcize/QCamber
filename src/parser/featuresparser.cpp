#include "featuresparser.h"

#include <QtCore>

void FeaturesDataStore::putSymbolName(const QString& line)
{
  QStringList param = line.split(" ");
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_symbolNameMap[id] = param[1];
  }
}

void FeaturesDataStore::putAttribName(const QString& line)
{
  QStringList param = line.split(" ");
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_attribNameMap[id] = param[1];
  }
}

void FeaturesDataStore::putAttribText(const QString& line)
{
  QStringList param = line.split(" ");
  if (param.length() == 2) {
    int id = param[0].right(param[0].length() - 1).toInt();
    m_attribTextMap[id] = param[1];
  }
}

void FeaturesDataStore::dump(void)
{
  qDebug() << "=== Symbol names ===";
  for (IDMapType::iterator it = m_symbolNameMap.begin();
      it != m_symbolNameMap.end(); ++it) {
    qDebug() << it.key() << it.value();
  }
  qDebug();

  qDebug() << "=== Attrib names ===";
  for (IDMapType::iterator it = m_attribNameMap.begin();
      it != m_attribNameMap.end(); ++it) {
    qDebug() << it.key() << it.value();
  }
  qDebug();

  qDebug() << "=== Attrib text ===";
  for (IDMapType::iterator it = m_attribTextMap.begin();
      it != m_attribTextMap.end(); ++it) {
    qDebug() << it.key() << it.value();
  }
}

FeaturesParser::FeaturesParser(const char* filename): Parser(filename)
{
}

FeaturesParser::FeaturesParser(QString filename): Parser(filename)
{
}

FeaturesParser::~FeaturesParser()
{
  
}

FeaturesDataStore* FeaturesParser::parse(void)
{
  FeaturesDataStore* ds = new FeaturesDataStore;
  QFile file(m_fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return NULL;

  while (!file.atEnd()) {
    QString line = file.readLine();
    line.chop(1); // remove newline character

    if (line.startsWith("#")) { // comment
      continue;
    } else if (line.startsWith("$")) { // symbol names
      ds->putSymbolName(line);
    } else if (line.startsWith("@")) { // attrib names
      ds->putAttribName(line);
    } else if (line.startsWith("&")) { // attrib text strings
      ds->putAttribText(line);
    }
  }
  return ds;
}
