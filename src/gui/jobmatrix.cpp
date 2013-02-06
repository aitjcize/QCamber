#include "jobmatrix.h"
#include "ui_jobmatrix.h"

JobMatrix::JobMatrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JobMatrix)
{
    ui->setupUi(this);
}

JobMatrix::~JobMatrix()
{
    delete ui;
}

void JobMatrix::on_CloseButton_clicked()
{
    this->close();
}
