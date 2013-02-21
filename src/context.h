#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "archiveloader.h"
#include "featuresparser.h"
#include "config.h"

#include <QGraphicsScene>

struct Context {
  ~Context() { delete loader; }

  ArchiveLoader* loader;    // loader
  Config* config;
  QColor bg_color;
};

#endif /* __CONTEXT_H__ */
