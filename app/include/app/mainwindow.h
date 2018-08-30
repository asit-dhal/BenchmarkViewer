/** @file mainwindow.h
 *  @brief Header for MainWindow
 *
 *  This creates all the child View(Benchmark Table View
 *  and Chart View. This also contains all actions for main window.
 *
 *  @author Asit Dhal (asit-dhal)
 **/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "model/measurement.h"

class QAction;
class QLineEdit;

namespace view {
class BenchmarkView;
class ChartView;
}  // namespace view

namespace model {
class BenchmarkModel;
}  // namespace model

class MainWindowPresenter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  void init();

  ~MainWindow();
  QAction* getOpenFileAction();
  QVector<QAction*> getOpenRecentFileActions();
  QVector<QAction*> getCloseFileActions();
  QVector<QAction*> getColumnVisibilityActions();
  QVector<QAction*> getColumnPlotStatusActions();
  QAction* getCloseAllFilesAction();
  QAction* getExportChartAction();
  QAction* getExitAction();
  QAction* getAboutApp();

  QLineEdit* getBenchmarkFilterWidget();

  void updateRecentFileActions(QStringList recentFiles);
  void updateOpenFileActions(QStringList openFiles);
  void updateViewColumnMenus(
      QMap<model::Measurement::Attributes, bool> colVisibility);
  void updateColumnPlotActions(
      QMap<model::Measurement::Attributes, bool> colPlotStatus);

  view::BenchmarkView* getBenchmarkView() const;

 signals:

 private:
  void createBenchmarkView();
  void createChartView();
  void createPresenter();
  void createModels();
  void closeEvent(QCloseEvent*);

 private:
  Ui::MainWindow* ui;
  QLineEdit* m_filter;
  MainWindowPresenter* m_presenter;
  view::BenchmarkView* m_benchmarkView;
  view::ChartView* m_chartView;
  QVector<QAction*> m_recentFileActions;
  QVector<QAction*> m_openFileActions;
  QVector<QAction*> m_columnVisibilityActions;
  QVector<QAction*> m_columnPlotStatusActions;
  model::BenchmarkModel* m_bmModel;
};

#endif  // MAINWINDOW_H
