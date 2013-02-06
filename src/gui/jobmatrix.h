#ifndef JOBMATRIX_H
#define JOBMATRIX_H

#include <QDialog>

namespace Ui {
class JobMatrix;
}

class JobMatrix : public QDialog
{
    Q_OBJECT
    
public:
    explicit JobMatrix(QWidget *parent = 0);
    ~JobMatrix();
    
private slots:
    void on_CloseButton_clicked();

private:
    Ui::JobMatrix *ui;
};

#endif // JOBMATRIX_H
