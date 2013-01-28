#ifndef __ARCHIVE_LOADER_H__
#define __ARCHIVE_LOADER_H__

#define TAR_COMMAND "tar"

#include <QDir>
#include <QString>

class ArchiveLoader {
public:
  ArchiveLoader(const char* filename = NULL);
  ~ArchiveLoader();

  bool load(const char* filename = NULL);

  QStringList getSteps(void);
  QStringList getLayers(void);
  QStringList getSymbols(void);

private:
  QDir m_dir;
  QString m_fileName;
};

#endif /* __ARCHIVE_LOADER_H__ */
