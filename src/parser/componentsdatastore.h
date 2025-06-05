#ifndef __COMPONENTS_DATASTORE_H__
#define __COMPONENTS_DATASTORE_H__

#include "datastore.h"
#include <QList>
#include <QString>

class ComponentRecord;
class PackageDataStore;

class ComponentsDataStore : public DataStore {
public:
  ComponentsDataStore();
  ~ComponentsDataStore();

  void setStepName(const QString& name) { m_step = name; }
  QString stepName() const { return m_step; }

  void setPackages(PackageDataStore* pkgs) { m_pkgs = pkgs; }
  PackageDataStore* packages() const { return m_pkgs; }

  void putRecord(ComponentRecord* rec);
  const QList<ComponentRecord*>& records() const { return m_records; }

  virtual void dump(void) {}

private:
  QString m_step;
  PackageDataStore* m_pkgs;
  QList<ComponentRecord*> m_records;
};

#endif /* __COMPONENTS_DATASTORE_H__ */
