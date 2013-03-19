#include "featurepropertiesdialog.h"
#include "ui_featurepropertiesdialog.h"

FeaturePropertiesDialog::FeaturePropertiesDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::FeaturePropertiesDialog)
{
  ui->setupUi(this);
}

FeaturePropertiesDialog::~FeaturePropertiesDialog()
{
  delete ui;
}

void FeaturePropertiesDialog::update(Symbol* symbol)
{
  ui->detail->setText(symbol->longInfoText());
  AttribData attrib = symbol->attrib();
  QString attribText;
  for (AttribData::iterator it = attrib.begin(); it != attrib.end(); ++it)  {
    attribText += QString("%1\t= %2\n").arg(it.key()).arg(it.value());
  }
  ui->attrib->setText(attribText);
}
