#include "jobmatrix.h"
#include "ui_jobmatrix.h"
#include "structuredtextparser.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"
#include "QGroupBox"
#include "QGridLayout"
#include <QStandardItemModel>

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
    int steps,layers;

    StructuredTextDataStore::BlockIterPair ip = ds->getBlocksByKey("STEP");
    steps = 2;
    for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    {
        QLabel *label = new QLabel();
        label->setText((QString)it->second->get("NAME").c_str());
        matrix_layout->addWidget(label,0,steps++);

    }

    ip = ds->getBlocksByKey("LAYER");
    layers = 1;
    for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    {
        QLabel *label = new QLabel();
        QString text;
        text = (QString)it->second->get("TYPE").c_str();
        if(text == "SILK_SCREEN")
            text = "(ss ,";
        else if(text == "SOLDER_MASK")
            text = "(sm ,";
        else if(text == "SIGNAL")
            text = "(sig,";
        else if(text == "DRILL")
            text = "(srl,";
        else if(text == "DOCUMENT")
            text = "(doc,";
        else if(text == "ROUT")
            text = "(rt ,";
        else if(text == "SOLDER_PASTE")
            text = "(sp ,";
        else
            text = "( ,";
        if(it->second->get("POLARITY") == "POSITIVE")
            text += "p)  ";
        else
            text += "n)  ";
        text += (QString)it->second->get("NAME").c_str();
        label->setText(text);
        //label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Plain);
        matrix_layout->addWidget(label,layers++,0);

        for(int i=2;i<steps;i++)
        {
            QPushButton *btn = new QPushButton;

            matrix_layout->addWidget(btn,layers-1,i);
        }

    }
    ui->matrix->setLayout(matrix_layout);
}
