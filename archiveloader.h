#ifndef __ARCHIVE_LOADER_H__
#define __ARCHIVE_LOADER_H__

#define TAR_COMMAND "tar"

#include <QDir>
#include <QString>

class ArchiveLoader {
public:
  ArchiveLoader(QString filename);
  ~ArchiveLoader();

  bool load(void);

  QString absPath(QString path);
  QStringList listDir(QString filename);

private:
  QDir m_dir;
  QString m_fileName;
};

#endif /* __ARCHIVE_LOADER_H__ */
