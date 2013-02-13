#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mylabel.h"
#include "QLayoutItem"
#include <QSignalMapper>
#include "odbppviewwidget.h"
#include "QFile"
#include "structuredtextparser.h"
#include "context.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addLayerLabel(QList<QString> *);
    void clearLayerLabel();
    void clearLayout(QLayout* , bool deleteWidgets = true);

private slots:
    void ShowLayer(const QString);

private:
    Ui::MainWindow *ui;
    QSignalMapper *layerSignalMapper;
    ODBPPViewWidget widget;

};

#endif // MAINWINDOW_H
