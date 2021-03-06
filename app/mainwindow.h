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

#pragma once

#include <QLoggingCategory>
#include <QMainWindow>
#include <QMap>
#include <QPoint>
#include <QStack>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QThread>
#include "benchmark.h"
#include "worker.h"
#include "mainwindow_presenter.h"

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

class MainWindow : public QMainWindow {
	Q_OBJECT

 public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();
	void setRecentFileActions(QList<QAction*> recentFileActions);
	void setCloseFileActions(QList<QAction*> closeFileActions);
	void setViewColumnActions(QList<QAction*> viewColumnActions);

 signals:
	void newFileSelected(ParserType, QString);
	void selectedFileDeleted(QString);

 private:
	void createActions();
	void createMenus();
	void createWidgets();
	void connectSignalsToSlots();
	void init();

 private slots:
    void onBenchmarkFilter(QString filter);
    void onSelectionChanged(const QItemSelection& selected,
                            const QItemSelection& deselected);
	void onPlotSelection();
	void onPlotAllRows();
	void onClearSelection();
	void onClearAllRows();

public:
	QAction* getOpenFileAction();
	QAction* getCloseAllFilesAction();
	QAction* getExportChartAction();
	QAction* getExitAction();
	QAction* getAboutBenchmarkAppAction();

 private:
	QMenu* m_fileMenu;
	QMenu* m_recentFileMenu;
	QMenu* m_closeFileMenu;
	QMenu* m_helpMenu;

	QAction* m_openFileAction;
	QList<QAction*> m_openRecentFilesAction;
	QList<QAction*> m_closeFileActions;
	QAction* m_closeAllFilesAction;
	QAction* m_exportChart;
	QAction* m_exitAction;

	QAction* m_toogleSelectedFileWidget;
	QAction* m_aboutApp;

	QStack<QString> m_files;
	QListWidget* m_selectedFilesWidget;
    QItemSelectionModel* m_selectionModel;
	BenchmarkView* m_benchmarkView;
	BenchmarkDelegate* m_benchmarkDelegate;
	
	IAbstractParser* m_parser;
	QChart* m_chart;
	QLineEdit* m_benchmarkNameFilter;

	MainWindowPresenter *m_mainWindowPresenter;
};
