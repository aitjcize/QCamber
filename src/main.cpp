#include <QtGui>

#include "code39.h"
#include "context.h"
#include "jobmatrix.h"
#include "settings.h"
#include "structuredtextparser.h"
#include "layerinfobox.h"

//#define DEPLOY

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Code39::initPatterns();
  QApplication::setGraphicsSystem("raster");

#ifdef DEPLOY
  QFileDialog diag(NULL, "Choose a tarball", "",
      "ODB++ database (*.tgz *.tar.gz)");
  diag.exec();

  QString sel = diag.selectedFiles()[0];
  if (QFileInfo(sel).isDir()) {
    exit(1);
  } else if (!sel.endsWith(".tgz") && !sel.endsWith(".tar.gz")) {
    QMessageBox::critical(NULL, "Error", "Invalid file format.");
    exit(1);
  }
  ctx.loader = new ArchiveLoader(diag.selectedFiles()[0]);
#else
  ctx.loader = new ArchiveLoader("demo.tgz");
#endif
  Settings::load("config.ini");
  ctx.bg_color = QColor(SETTINGS->get("Color", "BG").toString());

  StructuredTextParser parser(ctx.loader->absPath("matrix/matrix"));
  StructuredTextDataStore* ds = parser.parse();

  JobMatrix table(0, ds);
  table.SetMatrix();
  table.show();

  return app.exec();
}
