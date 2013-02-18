#ifndef __ARCHIVE_LOADER_H__
#define __ARCHIVE_LOADER_H__

#define TAR_COMMAND "tar"
#define GZIP_COMMAND "gzip"

#include <QDir>
#include <QString>
#include <QStringList>

class ArchiveLoader {
public:
  ArchiveLoader(QString filename);
  ~ArchiveLoader();

  bool load(void);

  QString absPath(QString path);
  QStringList listDir(QString filename);
  QString featuresPath(QString base);

private:
  bool recurRemove(const QString& dirname);

private:
  QDir m_dir;
  QString m_fileName;
};

#endif /* __ARCHIVE_LOADER_H__ */
