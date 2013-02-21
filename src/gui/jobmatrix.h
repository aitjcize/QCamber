#ifndef JOBMATRIX_H
#define JOBMATRIX_H

#include <QDialog>
#include "structuredtextparser.h"
#include "odbppgraphicsview.h"
#include <QSignalMapper>
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
  explicit JobMatrix(QWidget *parent = 0);
  void SetMatrix(StructuredTextDataStore* );
  ~JobMatrix();

private slots:
  void on_CloseButton_clicked();
  void showLayer(const QString);
  void showStep(const QString);

private:
  Ui::JobMatrix *ui;
  QStringList m_step_name;
  QStringList m_layer_name;
  ViewerWindow Window;
  QSignalMapper *layerSignalMapper,*stepSignalMapper;
};

#endif // JOBMATRIX_H
