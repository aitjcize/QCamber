#ifndef __ARCHIVE_LOADER_H__
#define __ARCHIVE_LOADER_H__

#ifdef Q_WS_WIN
# define TAR_COMMAND "tools/tar.exe"
# define GZIP_COMMAND "tools/gzip.exe"
#else
# define TAR_COMMAND "tar"
# define GZIP_COMMAND "gzip"
#endif

#include <QDir>
#include <QString>
#include <QStringList>

class ArchiveLoader {
public:
  ArchiveLoader(QString filename);
  ~ArchiveLoader();

  QString absPath(QString path);
  QStringList listDir(QString filename);
  QString featuresPath(QString base);

private:
  QDir m_dir;
  QString m_fileName;
};

#endif /* __ARCHIVE_LOADER_H__ */
