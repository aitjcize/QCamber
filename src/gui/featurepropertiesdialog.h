#ifndef __FEATUREPROPERTIESDIALOG_H__
#define __FEATUREPROPERTIESDIALOG_H__

#include <QDialog>

#include "symbol.h"

namespace Ui {
  class FeaturePropertiesDialog;
}

class FeaturePropertiesDialog : public QDialog
{
  Q_OBJECT

public:
  explicit FeaturePropertiesDialog(QWidget *parent = 0);
  ~FeaturePropertiesDialog();

public slots:
  void update(Symbol* symbol);

private:
  Ui::FeaturePropertiesDialog *ui;
};

#endif // __FEATUREPROPERTIESDIALOG_H__
