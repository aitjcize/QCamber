#include "jobmatrix.h"
#include "ui_jobmatrix.h"
#include "structuredtextparser.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"
#include "QGroupBox"
#include "QGridLayout"

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

void JobMatrix::ShowMatrix(StructuredTextDataStore* ds)
{
    QGridLayout *matrix_layout = new QGridLayout;
    int i;

    StructuredTextDataStore::BlockIterPair ip = ds->getBlocksByKey("STEP");
    i = 2;
    for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    {
        QLabel *label = new QLabel();
        label->setText((QString)it->second->get("NAME").c_str());
        matrix_layout->addWidget(label,0,i++);

    }

    ip = ds->getBlocksByKey("LAYER");
    i = 1;
    for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    {
        QLabel *label = new QLabel();
        label->setText((QString)it->second->get("NAME").c_str());
        matrix_layout->addWidget(label,i++,0);
    }
    ui->matrix->setLayout(matrix_layout);
}
