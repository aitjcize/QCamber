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

  //QFileDialog diag(NULL, "Choose a tarball", "", "ODB++ database (*.tgz)");
  //diag.exec();

  //ctx.loader = new ArchiveLoader(diag.selectedFiles()[0]);
  ctx.loader = new ArchiveLoader("demo.tgz");
  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  StructuredTextDataStore* ds = parser.parse();

  JobMatrix table;
  table.SetMatrix(ds);
  table.show();

  return app.exec();
}
