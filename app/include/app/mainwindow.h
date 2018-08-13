/*=========================================================================

   Program: QCommander

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   QCommander is a free software; you can redistribute it and/or modify it.


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
  QVector<QAction*> getColumnVisibilityActions();
  QAction* getCloseFileAction();
  QAction* getCloseAllFilesAction();
  QAction* getExportChartAction();
  QAction* getExitAction();
  QAction* getAboutApp();

  QLineEdit* getBenchmarkFilterWidget();

  void updateRecentFileActions(QStringList recentFiles);
  void updateViewColumnMenus(
      QMap<model::Measurement::Attributes, bool> colVisibility);

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
  QVector<QAction*> m_columnVisibilityActions;
  model::BenchmarkModel* m_bmModel;
};

#endif  // MAINWINDOW_H
