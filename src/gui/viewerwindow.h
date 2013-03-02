#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QColor>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QVBoxLayout>

#include "context.h"
#include "feature.h"
#include "layerinfobox.h"
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
  void setLayers(const QStringList& layers, const QStringList& types);
  void clearLayout(QLayout* , bool deleteWidgets = true);
  void showLayer(QString name);
  virtual void show(void);

public slots:
  void on_actionSetColor_triggered(void);

  void on_actionZoomIn_triggered(void);
  void on_actionZoomOut_triggered(void);
  void on_actionHome_triggered(void);
  void on_actionMousePan_toggled(bool checked);
  void on_actionAreaZoom_toggled(bool checked);
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
  void toggleShowLayer(bool selected);
  void layerActivated(bool status);
  void loadColorConfig();
  void unitChanged(int index);
  void updateCursorCoord(QPointF);
  void updateFeatureDetail(Symbol* symbol);

private:
  Ui::ViewerWindow *ui;
  QString m_step;
  QList<QColor> m_colors;
  QList<LayerInfoBox*> m_actives;
  QMap<int, bool> m_colorsMap;
  QMap<QString, LayerInfoBox*> m_SelectorMap;
  DisplayUnit m_displayUnit;
  QLabel* m_cursorCoordLabel;
  QLabel* m_featureDetailLabel;
  LayerInfoBox* m_activeInfoBox;
  bool m_transition;
};

#endif // __MAINWINDOW_H__
