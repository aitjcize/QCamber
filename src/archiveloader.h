#ifndef __ARCHIVE_LOADER_H__
#define __ARCHIVE_LOADER_H__

#ifdef Q_WS_WIN
# define TAR_CMD (QCoreApplication::applicationDirPath() + "tools/tar.exe")
# define GZIP_CMD (QCoreApplication::applicationDirPath() + "tools/gzip.exe")
#else
# define TAR_CMD "tar"
# define GZIP_CMD "gzip"
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
