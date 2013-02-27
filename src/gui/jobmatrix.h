#ifndef JOBMATRIX_H
#define JOBMATRIX_H

#include <QDialog>
#include <QSignalMapper>
#include <QTableWidget>

#include "structuredtextparser.h"
#include "odbppgraphicsview.h"
#include "clickablelabel.h"
#include "iostream"
#include "viewerwindow.h"

namespace Ui {
  class JobMatrix;
}

class JobMatrix : public QDialog
{
Q_OBJECT

public:
  explicit JobMatrix(QWidget *parent = 0, StructuredTextDataStore* ds = 0);
  void SetMatrix();
  ~JobMatrix();

private slots:
  void on_CloseButton_clicked();
  void showLayer(QTableWidgetItem *item);
  void drawDrillLine(QString layer_name, int start, int end);
  void selectDrillLine(int);

private:
  Ui::JobMatrix* ui;
  QStringList m_step_name;
  QStringList m_layer_name;
  StructuredTextDataStore *m_ds;
};

#endif // JOBMATRIX_H
