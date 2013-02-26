#include "symbolcount.h"
#include "ui_symbolcount.h"

symbolcount::symbolcount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::symbolcount)
{
    ui->setupUi(this);
}

symbolcount::~symbolcount()
{
    delete ui;
}
