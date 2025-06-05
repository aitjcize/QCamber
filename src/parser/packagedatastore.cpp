#include "packagedatastore.h"

void PackageDataStore::addPackage(int index, const PackageInfo& info)
{
  m_packages[index] = info;
}

PackageDataStore::PackageInfo PackageDataStore::package(int index) const
{
  return m_packages.value(index);
}
