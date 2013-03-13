#include <QtGui>

#include "code39.h"
#include "context.h"
#include "jobmanagerdialog.h"
#include "settings.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QApplication::setGraphicsSystem("raster");
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

  Code39::initPatterns();
  Settings::load("config.ini");
  ctx.bg_color = QColor(SETTINGS->get("Color", "BG").toString());

  JobManagerDialog dialog;
  dialog.show();

  return app.exec();
}
