#ifndef __ARCHIVE_LOADER_H__
#define __ARCHIVE_LOADER_H__

#define TAR_COMMAND "tar"

#include <string>
using std::string;

class ArchiveLoader {
public:
  ArchiveLoader(const char* filename = NULL);
  ~ArchiveLoader();

  bool load(const char* filename = NULL);

private:
  string m_fileName;
};

#endif /* __ARCHIVE_LOADER_H__ */
