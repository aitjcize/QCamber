#include <QtGui>

#include "jobmatrix.h"
#include "code39.h"
#include "context.h"
#include "structuredtextparser.h"

Context ctx;

#define DEPLOY

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Code39::initPatterns();

#ifdef DEPLOY
  QFileDialog diag(NULL, "Choose a tarball", "", "ODB++ database (*.tgz)");
  diag.exec();

  ctx.loader = new ArchiveLoader(diag.selectedFiles()[0]);
#else
  ctx.loader = new ArchiveLoader("demo2.tgz");
#endif
  ctx.config = new Config("config.ini");
  ctx.bg_color = QColor(ctx.config->value("color/BG").toString());

  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  StructuredTextDataStore* ds = parser.parse();

  JobMatrix table(0,ds);
  table.SetMatrix();
  table.show();

  return app.exec();
}
