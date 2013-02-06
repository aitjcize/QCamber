#ifndef JOBMATRIX_H
#define JOBMATRIX_H

#include <QDialog>
#include "structuredtextparser.h"


namespace Ui {
class JobMatrix;
}

class JobMatrix : public QDialog
{
    Q_OBJECT
    
public:
    explicit JobMatrix(QWidget *parent = 0);
    void ShowMatrix(StructuredTextDataStore* );
    ~JobMatrix();
    
private slots:
    void on_CloseButton_clicked();

private:
    Ui::JobMatrix *ui;
};

#endif // JOBMATRIX_H
