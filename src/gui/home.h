#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include "mylabel.h"
#include <QSignalMapper>
#include "QGridLayout"


#include "archiveloader.h"
#include "odbppviewwidget.h"
#include "structuredtextparser.h"
#include "featuresparser.h"
#include "fontparser.h"
#include "code39.h"
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
    void showJobPage(const QString jobName="");
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

#endif // HOME_H
