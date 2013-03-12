#include "archiveloader.h"

#include <QtCore>
#include <QFileInfo>
#include "parser.h"

ArchiveLoader::ArchiveLoader(QString filename): m_fileName(filename)
{
  m_dir = QDir(filename);
}

ArchiveLoader::~ArchiveLoader()
{
}

QString ArchiveLoader::absPath(QString path)
{
  return m_dir.absoluteFilePath(path);
}

QStringList ArchiveLoader::listDir(QString filename)
{
  QDir dir(m_dir.absoluteFilePath(filename));
  return dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
}

QString ArchiveLoader::featuresPath(QString base)
{
  QString plain_path = absPath(base.toLower() + "/features");

  // Ensure feature is not a gzipped file. If so, unzip it.
  QString path = plain_path;
  QFile file(path);

  if (!file.exists()) { // try .[zZ]
    file.setFileName(path + ".Z");

    if (file.exists()) {
      path += ".Z";
    } else {
      file.setFileName(path + ".z");
      if (!file.exists()) {
        return QString();
      }
      path += ".z";
    }

    QStringList args;
    args << "-d" << path;

    int ret = QProcess::execute(GZIP_CMD, args);

    if ((ret == -1) || (ret == -2)) {
      return QString();
    }
  }

  return plain_path;
}
