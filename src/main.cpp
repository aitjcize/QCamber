#include <QtGui>

#include "jobmatrix.h"
#include "code39.h"
#include "context.h"
#include "structuredtextparser.h"

Context ctx;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Code39::initPatterns();

  ctx.loader = new ArchiveLoader("demo.tgz");
  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  StructuredTextDataStore* ds = parser.parse();

  JobMatrix table;
  table.SetMatrix(ds);
  table.show();

  return app.exec();
}
