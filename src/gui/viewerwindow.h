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

namespace Ui {
class ViewerWindow;
}

class ViewerWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  typedef enum { U_INCH = 0, U_MM } DisplayUnit;

  explicit ViewerWindow(QWidget *parent = 0);
  ~ViewerWindow();
  void setStep(QString step);
  void setLayers(const QStringList& layerNames);
  void clearLayout(QLayout* , bool deleteWidgets = true);
  void showLayer(QString name);

public slots:
  void on_actionSetColor_triggered(void);

  void on_actionZoomIn_triggered(void);
  void on_actionZoomOut_triggered(void);
  void on_actionHome_triggered(void);
  void on_actionAreaZoom_triggered(void);
  void on_actionPanLeft_triggered(void);
  void on_actionPanRight_triggered(void);
  void on_actionPanUp_triggered(void);
  void on_actionPanDown_triggered(void);
  void on_actionHighlight_toggled(bool checked);
  void on_actionClearHighlight_triggered(void);
  void on_actionShowNotes_toggled(bool checked);

protected:
  QColor nextColor(void);

private slots:
  void toggleShowLayer(LayerSelector* selector, bool selected);
  void loadColorConfig();
  void unitChanged(int index);
  void updateCursorCoord(QPointF);
  void updateFeatureDetail(Symbol* symbol);

private:
  Ui::ViewerWindow *ui;
  QString m_step;
  QVBoxLayout* m_layout;
  QList<QColor> m_colors;
  QList<LayerSelector*> m_actives;
  QMap<int, bool> m_colorsMap;
  QMap<QString, LayerSelector*> m_SelectorMap;
  DisplayUnit m_displayUnit;
  QLabel* m_cursorCoordLabel;
  QLabel* m_featureDetailLabel;
};

#endif // __MAINWINDOW_H__
