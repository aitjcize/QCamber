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
  explicit JobMatrix(QString job, QWidget *parent = 0);
  ~JobMatrix();

  void setMatrix();

private slots:
  void on_CloseButton_clicked();
  void showLayer(QTableWidgetItem *item);
  void drawDrillLine(QString layer_name, int start, int end);
  void selectDrillLine(int);

private:
  Ui::JobMatrix* ui;
  QString m_job;
  QStringList m_stepNames;
  QStringList m_layerNames;
  QStringList m_layerTypes;
  StructuredTextDataStore *m_ds;
};

#endif // JOBMATRIX_H
