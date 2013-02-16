#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QLayoutItem"
#include "odbppviewwidget.h"
#include "QFile"
#include "structuredtextparser.h"
#include "context.h"
#include "layerselector.h"
#include "feature.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void addLayerLabel(const QStringList& layerNames);
  void clearLayout(QLayout* , bool deleteWidgets = true);
  void addProfile();

private slots:
  void showLayer(LayerSelector*, bool);

private:
  Ui::MainWindow *ui;
  Features* makeFeature(QString path, const QPen& pen,
      const QBrush& brush);
};

#endif // MAINWINDOW_H
