#include <QtGui>

#include "code39.h"
#include "context.h"
#include "settings.h"
#include "jobmanagerdialog.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QApplication::setGraphicsSystem("raster");

  // Some initializations
  Code39::initPatterns();
  Settings::load("config.ini");
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

  ctx.bg_color = QColor(SETTINGS->get("Color", "BG").toString());

  JobManagerDialog dialog;
  dialog.show();

  return app.exec();
}
