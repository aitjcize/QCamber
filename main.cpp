#include "parser.h"

#include <iostream>
#include <utility>

#include <QDebug>

#include "archiveloader.h"

using std::cout;
using std::endl;
using std::pair;

extern int yydebug;

int main(int argc, const char *argv[])
{
  yydebug = 0;
  ArchiveLoader a("demo.tgz");
  a.load();
  qDebug() << a.listDir("symbols");

  Parser parser(a.absPath("matrix/matrix"), Parser::STRUCTURED);
  StructuredDataStore* ds = (StructuredDataStore*)parser.parse();
  StructuredDataStore::BlockIterPair ip = ds->getBlocksByKey("STEP");

  for (StructuredDataStore::BlockIter it = ip.first; it != ip.second; ++it) {
    cout << it->second->get("NAME") << endl;;
  }

  return 0;
}
