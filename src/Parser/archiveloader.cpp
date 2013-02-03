#include "archiveloader.h"

#include <QtCore>

#include "parser.h"

ArchiveLoader::ArchiveLoader(QString filename): m_fileName(filename)
{
}

ArchiveLoader::~ArchiveLoader()
{
  recurRemove(m_dir.path());
}

bool ArchiveLoader::load(void)
{
  // Use `tar' command for the time being, may switch to libarchive in the
  // future.

  unsigned timestamp = QDateTime::currentDateTime().toTime_t();
  QString extract_dir = QString::number(timestamp) + "_" + m_fileName;

  QDir tempDir = QDir::temp();
  tempDir.mkdir(extract_dir);

  QString extract_name = tempDir.absoluteFilePath(extract_dir);

  QStringList args;
  args << "xf" << m_fileName << "--strip-components=1" << "-C" << extract_name;

  int ret = QProcess::execute(TAR_COMMAND, args);

  if ((ret != -1) && (ret != -2)) {
    m_dir = QDir(extract_name);
    return true;
  }

  return false;
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
}
