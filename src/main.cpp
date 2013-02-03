#include <iostream>
#include <utility>

#include <QtGui>
#include <QRegExp>

#include "archiveloader.h"
#include "odbppviewwidget.h"
#include "structuredtextparser.h"
#include "featuresparser.h"


using std::cout;
using std::endl;
using std::pair;

extern int yydebug;

int main(int argc, char *argv[])
{
  yydebug = 0;
  ArchiveLoader a("demo.tgz");
  a.load();
  qDebug() << a.listDir("symbols");

  StructuredTextParser parser(a.absPath("matrix/matrix"));
  StructuredTextDataStore* ds = parser.parse();
  StructuredTextDataStore::BlockIterPair ip = ds->getBlocksByKey("STEP");

  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    cout << it->second->get("NAME") << endl;;
  }

  FeaturesParser parser2("features");
  FeaturesDataStore* ds2 = parser2.parse();
  ds2->dump();

  QApplication app(argc, argv);

  ODBPPViewWidget widget;
  widget.show();
  return app.exec();
}
