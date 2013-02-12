#ifndef MAINVIEWER_H
#define MAINVIEWER_H

#include <QWidget>
#include "mylabel.h"
#include "QLayoutItem"
#include <QSignalMapper>
#include "odbppviewwidget.h"
#include "QFile"
#include "structuredtextparser.h"
#include "context.h"




namespace Ui {
class mainViewer;
}

class mainViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit mainViewer(QWidget *parent = 0);
    void addLayerLabel(QList<QString> *);
    void clearLayerLabel();
    void clearLayout(QLayout* , bool deleteWidgets = true);
    ~mainViewer();
private slots:
    void ShowLayer(const QString);
    
private:
    Ui::mainViewer *ui;
    QSignalMapper *layerSignalMapper;
    ODBPPViewWidget widget;

};

#endif // MAINVIEWER_H
