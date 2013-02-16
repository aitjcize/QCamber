#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QLayoutItem"
#include "odbppviewwidget.h"
#include "QFile"
#include "structuredtextparser.h"
#include "context.h"
#include "layerselector.h"
#include "feature.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void addLayerLabel(QList<QString> *);
  void clearLayout(QLayout* , bool deleteWidgets = true);
  void AddProfile();
  void AddCustomSymbol(QString);

private slots:
  void ShowLayer(Features*,int);

private:
  Ui::MainWindow *ui;
  Features *MakeFeature(QString filename,const QColor color = Qt::red,
      const QBrush brush = Qt::red);
};

#endif // MAINWINDOW_H
