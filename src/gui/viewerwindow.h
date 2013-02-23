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
  typedef enum { U_INCH = 0, U_MM } DisplayUnit;

  explicit ViewerWindow(QWidget *parent = 0);
  ~ViewerWindow();
  void setStep(QString step);
  void setLayers(const QStringList& layerNames);
  void clearLayout(QLayout* , bool deleteWidgets = true);
  void showLayer(QString name);

public slots:
  void on_actionSetColor_triggered(void);
  void on_homeFunc_clicked(void);
  void on_areaZoomFunc_clicked(void);
  void on_mousePanFunc_clicked(void);

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
