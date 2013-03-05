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

void symbolcount::addSymbolCount(QTextEdit *output)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(output);
    ui->scrollAreaWidgetContents->setLayout(layout);
}

void symbolcount::on_pushButton_clicked()
{
    this->close();
    delete ui->scrollAreaWidgetContents->layout();
}
