#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "archiveloader.h"
#include "featuresparser.h"

#include <QGraphicsScene>

struct Context {
  ~Context() { delete loader; }

  ArchiveLoader* loader;    // loader
};

#endif /* __CONTEXT_H__ */
