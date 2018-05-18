/*=========================================================================

   Program: BenchmarkViewer

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   BenchmarkViewer is a free software; you can redistribute it and/or modify it.


   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLoggingCategory>
#include <QMainWindow>
#include <QMap>
#include <QPoint>
#include <QStack>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include "benchmark.h"
#include "chartviewwidget.h"
#include "jsonparser.h"

QT_CHARTS_USE_NAMESPACE

class QMenu;
class QAction;
class QListWidget;
class BenchmarkModel;
class QTableView;
class BenchmarkView;
class QLineEdit;
class QPushButton;
class BenchmarkDelegate;
class BenchmarkProxyModel;
class QItemSelectionModel;
class QItemSelection;
class BmColumns;
class PlotConfig;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = 0);
  ~MainWindow();

 signals:
  void newFileSelected(QString);
  void selectedFileDeleted(QString);

 private:
  void createActions();
  void createMenus();
  void createWidgets();
  void connectSignalsToSlots();
  void updateRecentFileActions();
  void updateCloseFileActions();

 public slots:
  void onNewBenchmarks(QString filename, Benchmark benchmark);
  void onToggleColumnAction();
  void onUpdateColumnStatus();

 private slots:
  void onOpenFile();
  void onCloseFile(QString filename);
  void onCloseAllFiles();
  void onExportChart();
  void onExit();
  void onNewFileSelected(QString file);
  void onSelectedFilesWidgetContextMenu(const QPoint& pos);
  void onSelectedFileDeleted(QString file);
  void onToogleSelectedFileWidget();
  void onBenchmarkFilter(QString filter);
  void onAboutApp();
  void onSelectionChanged(const QItemSelection& selected,
                          const QItemSelection& deselected);
  void onPlotSelection();
  void onPlotAllRows();
  void onClearSelection();
  void onClearAllRows();

 private:
  QMenu* m_fileMenu;
  QMenu* m_recentFileMenu;
  QMenu* m_closeFileMenu;
  QMenu* m_viewMenu;
  QMenu* m_showColumnsSubMenu;
  QMenu* m_helpMenu;

  QAction* m_openFileAction;
  QList<QAction*> m_openRecentFilesAction;
  QList<QAction*> m_closeFileActions;
  QAction* m_closeAllFilesAction;
  QAction* m_exportChart;
  QAction* m_exitAction;

  QAction* m_toogleSelectedFileWidget;
  QList<QAction*> m_showColumns;
  QAction* m_aboutApp;

  QStack<QString> m_files;
  QListWidget* m_selectedFilesWidget;
  BenchmarkProxyModel* m_proxyModel;
  BenchmarkModel* m_benchmarkModel;
  QItemSelectionModel* m_selectionModel;
  BenchmarkView* m_benchmarkView;
  BenchmarkDelegate* m_benchmarkDelegate;
  BmColumns* m_bmColumns;
  AbstractParser* m_parser;
  QChart* m_chart;
  ChartViewWidget* m_chartView;
  PlotConfig* m_plotConfigWidget;
  QLineEdit* m_benchmarkNameFilter;
};

#endif  // MAINWINDOW_H
