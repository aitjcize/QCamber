#include "feature.h"

#include "context.h"
#include <typeinfo>
#include <QDebug>

extern Context ctx;

Features::Features(QString path): Symbol("features")
{
  FeaturesParser parser(path);
  m_ds = parser.parse();
  QList<Record*> records = m_ds->records();

  for (QList<Record*>::const_iterator it = records.begin();
      it != records.end(); ++it) {
    Record* rec = *it;
    rec->addToChild(this);
  }
}

Features::~Features()
{
  delete m_ds;
}

QTableWidget* Features::symbolCount()
{
    FeaturesDataStore::IDMapType nameMap;
    FeaturesDataStore::CountMapType countMap;
    QTableWidget *table = new QTableWidget;
    QTableWidgetItem * item;
    QStringList countData;
    int rowCount = 0;
    int total,local_total;
    nameMap = m_ds->symbolNameMap();
    table->setColumnCount(3);
    total = 0;

    rowCount+=5;
    local_total = 0;
    table->setRowCount(rowCount);
    item = new QTableWidgetItem("Line List");
    table->setItem(rowCount-2,0,item);
    item = new QTableWidgetItem("---------");
    table->setItem(rowCount-1,0,item);
    countMap = m_ds->posLineCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        table->setRowCount(++rowCount);
        QString text;
        text.sprintf("%d",countMap[i]);
        item = new QTableWidgetItem("POS");
        table->setItem(rowCount-1,0,item);
        item = new QTableWidgetItem(nameMap[i]);
        table->setItem(rowCount-1,1,item);
        item = new QTableWidgetItem(text);
        table->setItem(rowCount-1,2,item);
        local_total+=countMap[i];
      }
    }
    countMap = m_ds->negLineCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        table->setRowCount(++rowCount);
        QString text;
        text.sprintf("%d",countMap[i]);
        item = new QTableWidgetItem("NEG");
        table->setItem(rowCount-1,0,item);
        item = new QTableWidgetItem(nameMap[i]);
        table->setItem(rowCount-1,1,item);
        item = new QTableWidgetItem(text);
        table->setItem(rowCount-1,2,item);
        local_total+=countMap[i];
      }
    }
    table->setRowCount(rowCount+2);
    table->setItem(rowCount,0,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("-------"));
    table->setItem(rowCount++,2,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("Total"));
    table->setItem(rowCount++,2,new QTableWidgetItem(
                       QString().sprintf("%d",local_total)));
    total += local_total;

    rowCount+=3;
    local_total = 0;
    table->setRowCount(rowCount);
    item = new QTableWidgetItem("Pad List");
    table->setItem(rowCount-2,0,item);
    item = new QTableWidgetItem("--------");
    table->setItem(rowCount-1,0,item);
    countMap = m_ds->posPadCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        table->setRowCount(++rowCount);
        QString text;
        text.sprintf("%d",countMap[i]);
        item = new QTableWidgetItem("POS");
        table->setItem(rowCount-1,0,item);
        item = new QTableWidgetItem(nameMap[i]);
        table->setItem(rowCount-1,1,item);
        item = new QTableWidgetItem(text);
        table->setItem(rowCount-1,2,item);
        local_total+=countMap[i];
      }
    }
    countMap = m_ds->negPadCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        table->setRowCount(++rowCount);
        QString text;
        text.sprintf("%d",countMap[i]);
        item = new QTableWidgetItem("NEG");
        table->setItem(rowCount-1,0,item);
        item = new QTableWidgetItem(nameMap[i]);
        table->setItem(rowCount-1,1,item);
        item = new QTableWidgetItem(text);
        table->setItem(rowCount-1,2,item);
        local_total+=countMap[i];
      }
    }
    table->setRowCount(rowCount+2);
    table->setItem(rowCount,0,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("-------"));
    table->setItem(rowCount++,2,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("Total"));
    table->setItem(rowCount++,2,new QTableWidgetItem(
                       QString().sprintf("%d",local_total)));
    total += local_total;

    rowCount+=3;
    local_total = 0;
    table->setRowCount(rowCount);
    item = new QTableWidgetItem("Arch List");
    table->setItem(rowCount-2,0,item);
    item = new QTableWidgetItem("---------");
    table->setItem(rowCount-1,0,item);
    countMap = m_ds->posArchCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        table->setRowCount(++rowCount);
        QString text;
        text.sprintf("%d",countMap[i]);
        item = new QTableWidgetItem("POS");
        table->setItem(rowCount-1,0,item);
        item = new QTableWidgetItem(nameMap[i]);
        table->setItem(rowCount-1,1,item);
        item = new QTableWidgetItem(text);
        table->setItem(rowCount-1,2,item);
        local_total+=countMap[i];
      }
    }
    countMap = m_ds->negArchCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        table->setRowCount(++rowCount);
        QString text;
        text.sprintf("%d",countMap[i]);
        item = new QTableWidgetItem("NEG");
        table->setItem(rowCount-1,0,item);
        item = new QTableWidgetItem(nameMap[i]);
        table->setItem(rowCount-1,1,item);
        item = new QTableWidgetItem(text);
        table->setItem(rowCount-1,2,item);
        local_total+=countMap[i];
      }
    }
    table->setRowCount(rowCount+2);
    table->setItem(rowCount,0,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("-------"));
    table->setItem(rowCount++,2,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("Total"));
    table->setItem(rowCount++,2,new QTableWidgetItem(
                       QString().sprintf("%d",local_total)));
    total += local_total;

    rowCount+=3;
    local_total = 0;
    table->setRowCount(rowCount);
    item = new QTableWidgetItem("Surface List");
    table->setItem(rowCount-2,0,item);
    item = new QTableWidgetItem("------------");
    table->setItem(rowCount-1,0,item);
    countMap = m_ds->posSurfaceCountMap();
    if(countMap[0] != 0){
      ++rowCount;
      table->setRowCount(rowCount);
      QString text;
      text.sprintf("%d",countMap[0]);
      item = new QTableWidgetItem("POS");
      table->setItem(rowCount-1,0,item);
      item = new QTableWidgetItem(text);
      table->setItem(rowCount-1,1,item);
      local_total+=countMap[0];
    }
    countMap = m_ds->negSurfaceCountMap();
    if(countMap[0] != 0)
    {
      ++rowCount;
      table->setRowCount(rowCount);
      QString text;
      text.sprintf("%d",countMap[0]);
      item = new QTableWidgetItem("NEG");
      table->setItem(rowCount-1,0,item);
      item = new QTableWidgetItem(text);
      table->setItem(rowCount-1,1,item);
      local_total+=countMap[0];
    }
    table->setRowCount(rowCount+2);
    table->setItem(rowCount,0,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("-------"));
    table->setItem(rowCount++,2,new QTableWidgetItem("-------"));
    table->setItem(rowCount,1,new QTableWidgetItem("Total"));
    table->setItem(rowCount++,2,new QTableWidgetItem(
                       QString().sprintf("%d",local_total)));
    total += local_total;

    table->setItem(0,0,new QTableWidgetItem("Total"));
    table->setItem(0,2,new QTableWidgetItem(
                       QString().sprintf("%d",total)));
    table->setItem(1,0,new QTableWidgetItem("-------"));
    table->setItem(1,1,new QTableWidgetItem("-------"));
    table->setItem(1,2,new QTableWidgetItem("-------"));


    return table;
}













