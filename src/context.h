#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "archiveloader.h"
#include "featuresparser.h"

#include <QGraphicsScene>

struct Context {
  ArchiveLoader* loader;    // loader
  FeaturesDataStore* cfds;  // current feature datastore
  QGraphicsScene* cscene;
};

#endif /* __CONTEXT_H__ */
