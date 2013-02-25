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

void Features::symbolCount()
{
    FeaturesDataStore::IDMapType nameMap;
    FeaturesDataStore::CountMapType countMap;
    QStringList countData;
    nameMap = m_ds->symbolNameMap();

    countData.append("Line List");
    countData.append("---------");
    countMap = m_ds->posLineCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        QString text;
        text.sprintf("POS\t%s,\t\t%d",nameMap[i].toAscii().data(),countMap[i]);
        countData.append(text);
      }
    }
    countMap = m_ds->negLineCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        QString text;
        text.sprintf("NEG\t%s,\t\t%d",nameMap[i].toAscii().data(),countMap[i]);
        countData.append(text);
      }
    }
    countData.append("Pad List");
    countData.append("---------");
    countMap = m_ds->posPadCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        QString text;
        text.sprintf("POS\t%s,\t\t%d",nameMap[i].toAscii().data(),countMap[i]);
        countData.append(text);
      }
    }
    countMap = m_ds->negPadCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        QString text;
        text.sprintf("NEG\t%s,\t\t%d",nameMap[i].toAscii().data(),countMap[i]);
        countData.append(text);
      }
    }
    countData.append("Arch List");
    countData.append("---------");
    countMap = m_ds->posArchCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        QString text;
        text.sprintf("POS\t%s,\t\t%d",nameMap[i].toAscii().data(),countMap[i]);
        countData.append(text);
      }
    }
    countMap = m_ds->negArchCountMap();
    for(int i = 0;i < countMap.size();i++){
      if(countMap[i] != 0){
        QString text;
        text.sprintf("NEG\t%s,\t\t%d",nameMap[i].toAscii().data(),countMap[i]);
        countData.append(text);
      }
    }
    countData.append("Surface List");
    countData.append("------------");
    countMap = m_ds->posSurfaceCountMap();
    if(countMap[0] != 0){
      QString text;
      text.sprintf("POS\t\t%d",countMap[0]);
      countData.append(text);
    }
    countMap = m_ds->negSurfaceCountMap();
    if(countMap[0] != 0)
    {
      QString text;
      text.sprintf("NEG\t\t%d",countMap[0]);
      countData.append(text);
    }

    for(int i=0;i<countData.length();i++)
        qDebug()<<countData.at(i);
}













