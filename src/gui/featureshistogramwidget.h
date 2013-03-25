#ifndef FEATURESHISTOGRAMWIDGET_H
#define FEATURESHISTOGRAMWIDGET_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
  class FeaturesHistogramWidget;
}

class FeaturesHistogramWidget : public QWidget
{
Q_OBJECT

public:
  explicit FeaturesHistogramWidget(QWidget *parent = 0);
  ~FeaturesHistogramWidget();

  void setTreeViewModel(QStandardItemModel* model);

public slots:
  void on_treeView_expanded(const QModelIndex& index);

private:
  Ui::FeaturesHistogramWidget *ui;
};

#endif // FEATURESHISTOGRAMWIDGET_H
