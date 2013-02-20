#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QColor>
#include <QList>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QMap>

#include "context.h"
#include "feature.h"
#include "layerselector.h"
#include "odbppgraphicsview.h"
#include "structuredtextparser.h"
#include "colorsettings.h"

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

public slots:
  void on_actionSetColor_triggered();

protected:
  Features* makeFeature(QString path, const QPen& pen, const QBrush& brush);
  QColor nextColor(void);

private slots:
  void showLayer(LayerSelector* layer, bool selected);
  void loadColorConfig();
  void showMouseCord(QPoint);

private:
  Ui::MainWindow *ui;
  QVBoxLayout* m_layout;
  QVBoxLayout* m_tool_layout;
  QList<QColor> m_colors;
  QMap<int, bool> m_colorsMap;
  ColorSettings m_color_widget;
  myLabel* m_statusLabel;
};

#endif // __MAINWINDOW_H__
