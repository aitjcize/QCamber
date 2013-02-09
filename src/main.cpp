#include <iostream>
#include <utility>

#include <QtGui>
#include <QRegExp>

#include "archiveloader.h"
#include "odbppviewwidget.h"
#include "structuredtextparser.h"
#include "featuresparser.h"
#include "fontparser.h"
#include "code39.h"
#include "context.h"

Context ctx;

using std::cout;
using std::endl;

extern int yydebug;

int main(int argc, char *argv[])
{
  Code39::initPatterns();

  yydebug = 0;
  ctx.loader = new ArchiveLoader("demo.tgz");

  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  StructuredTextDataStore* ds = parser.parse();
  StructuredTextDataStore::BlockIterPair ip = ds->getBlocksByKey("STEP");

  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    cout << it->second->get("NAME") << endl;;
  }

  QApplication app(argc, argv);

  ODBPPViewWidget widget;
  widget.show();
  return app.exec();
}
