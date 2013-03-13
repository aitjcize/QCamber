#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "archiveloader.h"
#include "featuresparser.h"

#include <QGraphicsScene>

struct Context {
  Context();
  ~Context() { delete loader; }

  ArchiveLoader* loader;    // loader
  QColor bg_color;
};

extern Context ctx;

#endif /* __CONTEXT_H__ */
