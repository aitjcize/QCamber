#include "componentsdatastore.h"
#include "packagedatastore.h"
#include "record.h"

ComponentsDataStore::ComponentsDataStore() : m_pkgs(NULL)
{
}

ComponentsDataStore::~ComponentsDataStore()
{
  qDeleteAll(m_records);
}

void ComponentsDataStore::putRecord(ComponentRecord* rec)
{
  m_records.append(rec);
}
