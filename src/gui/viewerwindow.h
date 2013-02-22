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
class ViewerWindow;
}

class ViewerWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit ViewerWindow(QWidget *parent = 0);
  ~ViewerWindow();
  void setStep(QString step);
  void setLayers(const QStringList& layerNames);
  void clearLayout(QLayout* , bool deleteWidgets = true);
  void showLayer(QString name);
  void loadActionBtn();

public slots:
  void on_actionSetColor_triggered();
  void fitViewerScreen();

protected:
  QColor nextColor(void);

private slots:
  void toggleShowLayer(LayerSelector* selector, bool selected);
  void loadColorConfig();
  void updateCursorCoord(QPointF);
  void updateFeatureDetail(Symbol* symbol);

private:
  Ui::ViewerWindow *ui;
  QString m_step;
  QVBoxLayout* m_layout;
  QVBoxLayout* m_tool_layout;
  QList<QColor> m_colors;
  QList<LayerSelector*> m_actives;
  QMap<int, bool> m_colorsMap;
  QMap<QString, LayerSelector*> m_SelectorMap;
  QLabel* m_cursorCoordLabel;
  QLabel* m_featureDetailLabel;
};

#endif // __MAINWINDOW_H__
