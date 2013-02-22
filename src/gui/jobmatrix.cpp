#include "jobmatrix.h"
#include "ui_jobmatrix.h"
#include "structuredtextparser.h"
#include "context.h"
#include "QDebug"
#include <QtGui>

extern Context ctx;

using namespace std;

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

void JobMatrix::SetMatrix(StructuredTextDataStore* ds)
{
  StructuredTextDataStore::BlockIterPair ip;
  QString text;
  layerSignalMapper = new QSignalMapper(this);
  stepSignalMapper = new  QSignalMapper(this);
  int steps,layers;

  steps = layers = 0;
  ip = ds->getBlocksByKey("STEP");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    steps++;
  ip = ds->getBlocksByKey("LAYER");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
    layers++;

  ui->tableWidget->setColumnCount(steps);
  ui->tableWidget->setRowCount(layers);

  steps = 1;
  ip = ds->getBlocksByKey("STEP");
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    ClickableLabel *label = new ClickableLabel("this");
    label->setText(QString::fromStdString(it->second->get("NAME")));
    m_step_name.append(QString::fromStdString(it->second->get("NAME")));
    //ui->tableWidget.setHorizontalHeaderItem(steps+1,label);

    steps++;
    connect(label, SIGNAL(clicked()), stepSignalMapper, SLOT(map()));
    stepSignalMapper->setMapping(label, QString::fromStdString(
          it->second->get("NAME")));
  }

  layers = 0;
  ip = ds->getBlocksByKey("LAYER");

  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    QTableWidgetItem *item = new QTableWidgetItem();
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
    m_layer_name.append((QString)it->second->get("NAME").c_str());
    text += (QString)it->second->get("NAME").c_str();
    item->setText(text);
    ui->tableWidget->setVerticalHeaderItem(layers, item);

    for(int i = 0; i < m_step_name.size(); i++)
    {
      text = m_step_name[i] + "/" + (QString)it->second->get("NAME").c_str();
      QPushButton *btn = new QPushButton(text);
      connect(btn, SIGNAL(clicked()), layerSignalMapper, SLOT(map()));
      layerSignalMapper->setMapping(btn, text);
      ui->tableWidget->setCellWidget(layers, i, btn);

      QString pathTmpl = "steps/%1/layers/%2";
      text = pathTmpl.arg(m_step_name[i].toAscii().data()).arg(
          QString::fromStdString(it->second->get("NAME")));

      if (QFile(ctx.loader->featuresPath(text)).size() == 0) {
        //btn->setFlat(true);
        btn->setText("");
      }
    }
    layers++;
  }

  connect(layerSignalMapper, SIGNAL(mapped (const QString &)), this,
      SLOT(showLayer(const QString &)));
  ui->tableWidget->verticalHeader()->setMovable(true);
}

void JobMatrix::showLayer(const QString text)
{
  QStringList params = text.split("/");
  ViewerWindow* w = new ViewerWindow;
  w->setStep(params[0]);
  w->setLayers(m_layer_name);
  w->showLayer(params[1]);
  w->show();
}
