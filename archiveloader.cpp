#include "archiveloader.h"

ArchiveLoader::ArchiveLoader(const char* filename): m_fileName(filename)
{
  if (filename) {
  }
}

ArchiveLoader::~ArchiveLoader()
{
  
}

bool ArchiveLoader::load(const char* filename)
{
  if (filename) {
    m_fileName = filename;
  }
}
