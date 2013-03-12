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
  recurRemove(m_dir.path());
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

bool ArchiveLoader::recurRemove(const QString& dirname)
{
  bool result = true;
  QDir dir(dirname);

  if (dir.exists(dirname)) {
    Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot |
          QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files,
          QDir::DirsFirst)) {
      if (info.isDir()) {
        result = recurRemove(info.absoluteFilePath());
      }
      else {
        result = QFile::remove(info.absoluteFilePath());
      }

      if (!result) {
        return result;
      }
    }
    result = dir.rmdir(dirname);
  }
  return result;
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

    int ret = QProcess::execute(GZIP_COMMAND, args);

    if ((ret == -1) || (ret == -2)) {
      return QString();
    }
  }

  return plain_path;
}
