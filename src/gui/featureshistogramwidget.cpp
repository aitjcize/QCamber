#include "featureshistogramwidget.h"
#include "ui_featureshistogramwidget.h"

#include <QtGui>

FeaturesHistogramWidget::FeaturesHistogramWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FeaturesHistogramWidget)
{
  ui->setupUi(this);
}

FeaturesHistogramWidget::~FeaturesHistogramWidget()
{
  delete ui;
}

void FeaturesHistogramWidget::setTreeViewModel(QStandardItemModel* model)
{
  ui->treeView->setModel(model);
  ui->treeView->resizeColumnToContents(0);
  ui->treeView->resizeColumnToContents(1);
  ui->treeView->show();
}

void FeaturesHistogramWidget::on_treeView_expanded(const QModelIndex& index)
{
  ui->treeView->resizeColumnToContents(index.column());
}
