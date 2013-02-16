#include <QtGui>

#include "home.h"
#include "jobmatrix.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  //ODBPPViewWidget widget;
  //widget.show();
  JobMatrix table;
  table.SetMatrix(ds);
  table.show();
  //Home HomeWindow;
  //HomeWindow.show();

  return app.exec();
}
