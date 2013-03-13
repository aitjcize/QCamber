#include <QtGui>

#include "jobmanagerdialog.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QApplication::setGraphicsSystem("raster");
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

  JobManagerDialog dialog;
  dialog.show();

  return app.exec();
}
