#ifndef JOBMATRIX_H
#define JOBMATRIX_H

#include <QDialog>
#include "structuredtextparser.h"
#include "odbppviewwidget.h"
#include <QSignalMapper>
#include "mylabel.h"
#include "iostream"
#include "mainwindow.h"

namespace Ui {
  class JobMatrix;
}

class JobMatrix : public QDialog
{
Q_OBJECT

public:
  explicit JobMatrix(QWidget *parent = 0);
  void SetMatrix(StructuredTextDataStore* );
  ~JobMatrix();

private slots:
  void on_CloseButton_clicked();
  void showLayer(const QString);
  void showStep(const QString);

private:
  Ui::JobMatrix *ui;
  unsigned long GetFileLength (QString);
  QStringList step_name, layer_name;
  ODBPPViewWidget widget;
  MainWindow Window;
  //MainWindow Window;
  QSignalMapper *layerSignalMapper,*stepSignalMapper;
};

#endif // JOBMATRIX_H
