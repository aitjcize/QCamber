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
  QGridLayout *matrix_layout = new QGridLayout;
  layerSignalMapper = new QSignalMapper(this);
  stepSignalMapper = new  QSignalMapper(this);
  QString text;
  int steps,layers;

  StructuredTextDataStore::BlockIterPair ip = ds->getBlocksByKey("STEP");
  steps = 2;
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    ClickableLabel *label = new ClickableLabel("this");
    label->setText((QString)it->second->get("NAME").c_str());
    matrix_layout->addWidget(label,0,steps++);
    step_name.append((QString)it->second->get("NAME").c_str());

    connect(label, SIGNAL(clicked()),stepSignalMapper, SLOT(map()));
    stepSignalMapper->setMapping(label,(QString)it->second->get("NAME").c_str());
  }

  ip = ds->getBlocksByKey("LAYER");
  layers = 1;
  for (StructuredTextDataStore::BlockIter it = ip.first; it != ip.second; ++it)
  {
    QLabel *label = new QLabel();        
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
    layer_name.append((QString)it->second->get("NAME").c_str());
    text += (QString)it->second->get("NAME").c_str();
    label->setText(text);
    matrix_layout->addWidget(label,layers++,0);

    for(int i=2;i<steps;i++)
    {
      text = step_name[i-2] + "/" + (QString)it->second->get("NAME").c_str();
      QPushButton *btn = new QPushButton(text);
      connect(btn, SIGNAL(clicked()),layerSignalMapper, SLOT(map()));
      layerSignalMapper->setMapping(btn,text);


      QString pathTmpl = "steps/%1/layers/%2";
      text = pathTmpl.arg(step_name[i-2].toAscii().data()).arg(
          QString::fromStdString(it->second->get("NAME")));

      if (QFile(ctx.loader->featuresPath(text)).size() == 0) {
        //btn->setFlat(true);
        btn->setText("");
      }
      matrix_layout->addWidget(btn,layers-1,i);
    }
  }

  connect(stepSignalMapper, SIGNAL(mapped (const QString &)), this,
      SLOT(showStep(const QString &)));
  connect(layerSignalMapper, SIGNAL(mapped (const QString &)), this,
      SLOT(showLayer(const QString &)));
  ui->scrollWidget->setLayout(matrix_layout);
}

void JobMatrix::showLayer(const QString feature_name)
{
  QStringList name = feature_name.toLower().split("/");
  QString pathTmpl = "steps/%1/layers/%2";
  QString path = pathTmpl.arg(name[0]).arg(name[1]);
  widget.loadProfile(name[0]);
  widget.loadFeature(ctx.loader->featuresPath(path.toLower()));
  widget.show();
}

void JobMatrix::showStep(const QString step_name)
{
  Window.setWindowTitle(step_name);
  Window.addLayerLabel(layer_name);
  Window.show();
}
