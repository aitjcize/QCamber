#include "archiveloader.h"

#include <QDir>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDateTime>
#include <QDebug>

#include "parser.h"

ArchiveLoader::ArchiveLoader(QString filename): m_fileName(filename)
{
}

ArchiveLoader::~ArchiveLoader()
{
  
}

bool ArchiveLoader::load(void)
{
  // Use `tar' command for the time being, may switched to libarchive in the
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

QString ArchiveLoader::absPath(QString path) {
  return m_dir.absoluteFilePath(path);
}

QStringList ArchiveLoader::listDir(QString filename)
{
  QDir dir(m_dir.absoluteFilePath(filename));
  QStringList symbols = dir.entryList();
  symbols.removeAll(".");
  symbols.removeAll("..");
  return symbols;
}
