#ifndef __HOME_H__
#define __HOME_H__

#include <QMainWindow>
#include "mylabel.h"
#include <QSignalMapper>
#include "QGridLayout"


#include "archiveloader.h"
#include "structuredtextparser.h"
#include "featuresparser.h"
#include "fontparser.h"
#include "context.h"
#include "gui/jobmatrix.h"
#include "dirent.h"

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit Home(QWidget *parent = 0);
  ~Home();

private slots:
  void showHomePage();
  void showJobPage(const QString jobName = QString());
  void showMatrix();
  void showStep(const QString);
  void showSymbol(const QString);
  void showStepPage();
  void showCustomSymbolPage();

private:
  Ui::Home *ui;
  QSignalMapper *jobSignalMapper,*stepSignalMapper,*symbolSignalMapper;
  void clearLayout(QLayout* , bool deleteWidgets = true);
  QGridLayout *layout;
  JobMatrix *matrixptr;
  MainWindow *stepptr;
  StructuredTextDataStore* ds;
  QString currJob;
};

#endif // __HOME_H__
