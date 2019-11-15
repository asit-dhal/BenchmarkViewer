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

#include "mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QKeySequence>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QRegExp>
#include <QSplitter>
#include <QTableView>
#include "appconfig.h"
#include "benchmarkdelegate.h"
#include "benchmarkmodel.h"
#include "benchmarkproxymodel.h"
#include "benchmarkview.h"
#include "csvparser.h"
#include "globals.h"
#include "helper.h"
#include "chartviewwidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	init();
	createActions();
	createMenus();
	createWidgets();
	showMaximized();

	m_mainWindowPresenter = new MainWindowPresenter(this, this);
	connectSignalsToSlots();
}

MainWindow::~MainWindow() {}

void MainWindow::init()
{
	qRegisterMetaType<ParserType>("ParserType");
	qRegisterMetaType<Benchmark>("Benchmark");

    new BenchmarkModel(this);
    new BenchmarkProxyModel(this);
}

QAction* MainWindow::getOpenFileAction()
{
	return m_openFileAction;
}

QAction* MainWindow::getCloseAllFilesAction()
{
	return m_closeAllFilesAction;
}

QAction* MainWindow::getExportChartAction()
{
	return m_exportChart;
}

QAction* MainWindow::getExitAction()
{
	return m_exitAction;
}

QAction* MainWindow::getAboutBenchmarkAppAction()
{
	return m_aboutApp;
}


void MainWindow::createActions()
{
	m_openFileAction = new QAction(tr("&Open File(s)"), this);
	m_openFileAction->setShortcuts(QKeySequence::Open);

	m_closeAllFilesAction = new QAction(tr("Close All files"), this);
	m_closeAllFilesAction->setStatusTip(tr("Close All Files "));

	m_exportChart = new QAction(tr("Export Chart"), this);

	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setStatusTip(tr("Exit"));
	m_exitAction->setShortcuts(QKeySequence::Quit);

	m_aboutApp = new QAction(tr("About BenchmarkViewer"), this);
	m_aboutApp->setStatusTip(tr("About BenchmarkViewer"));
}

void MainWindow::setRecentFileActions(QList<QAction*> recentFileActions)
{
	qDeleteAll(m_openRecentFilesAction);
	m_openRecentFilesAction.clear();

	m_openRecentFilesAction.append(recentFileActions);

	foreach (QAction* recentFileAction, m_openRecentFilesAction)
	{
		m_recentFileMenu->addAction(recentFileAction);
	}
}

void MainWindow::setCloseFileActions(QList<QAction*> closeFileActions)
{
	qDeleteAll(m_closeFileActions);
	m_closeFileActions.clear();

	m_closeFileActions.append(closeFileActions);

	foreach (QAction* closeFileAction, m_closeFileActions)
	{
		m_closeFileMenu->addAction(closeFileAction);
	}
}

void MainWindow::createMenus() 
{
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_openFileAction);
	m_recentFileMenu = m_fileMenu->addMenu(tr("Recent Files"));
	m_closeFileMenu = m_fileMenu->addMenu(tr("Close File(s)"));

	m_fileMenu->addAction(m_closeAllFilesAction);
	m_fileMenu->addAction(m_exportChart);
	m_fileMenu->addAction(m_exitAction);

	m_helpMenu = menuBar()->addMenu(tr("&Help"));
	m_helpMenu->addAction(m_aboutApp);
}

void MainWindow::onSelectionChanged(const QItemSelection& selected,
                                    const QItemSelection& deselected)
{
	Q_UNUSED(selected);
	Q_UNUSED(deselected);
}

void MainWindow::createWidgets()
{
    QWidget* benckmarkSelector = new QWidget(this);
	m_benchmarkNameFilter = new QLineEdit(this);
	m_benchmarkNameFilter->setPlaceholderText(tr("Filter"));
	m_benchmarkView = new BenchmarkView(this);
	m_benchmarkDelegate = new BenchmarkDelegate(this);

    BenchmarkProxyModel::getInstance()->setSourceModel(BenchmarkModel::getInstance());
    m_benchmarkView->seBenchmarkColumnAttributes(BenchmarkModel::getInstance()); // strongly coupled
    m_benchmarkView->setModel(BenchmarkProxyModel::getInstance());
	m_benchmarkView->setItemDelegate(m_benchmarkDelegate);
	m_benchmarkView->setEditTriggers(QAbstractItemView::CurrentChanged);
	m_benchmarkView->setSortingEnabled(true);
	m_benchmarkView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_benchmarkView->sortByColumn(1, Qt::DescendingOrder);

    QHBoxLayout* benchmarkFilterLayout = new QHBoxLayout;
	benchmarkFilterLayout->addWidget(m_benchmarkNameFilter);
	QVBoxLayout* benchmarkLayout = new QVBoxLayout;
	benchmarkLayout->addLayout(benchmarkFilterLayout);
	benchmarkLayout->addWidget(m_benchmarkView);
    benckmarkSelector->setLayout(benchmarkLayout);

    new ChartViewWidget(this);

	QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(benckmarkSelector);
    splitter->addWidget(ChartViewWidget::getInstance());
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    setCentralWidget(splitter);

    m_selectionModel = new QItemSelectionModel(BenchmarkProxyModel::getInstance());
	m_benchmarkView->setSelectionModel(m_selectionModel);
}

void MainWindow::connectSignalsToSlots() 
{
    connect(m_benchmarkNameFilter, SIGNAL(textChanged(QString)), this, SLOT(onBenchmarkFilter(QString)));

    connect(BenchmarkModel::getInstance(), &BenchmarkModel::measurementActive,
            ChartViewWidget::getInstance(), &ChartViewWidget::onAddMeasurement);
    connect(BenchmarkModel::getInstance(), &BenchmarkModel::measurementInactive,
            ChartViewWidget::getInstance(), &ChartViewWidget::onRemoveMeasurement);

    connect(m_selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);
    connect(m_benchmarkView, &BenchmarkView::select, this, &MainWindow::onPlotSelection);
    connect(m_benchmarkView, &BenchmarkView::selectAllRows, this, &MainWindow::onPlotAllRows);
    connect(m_benchmarkView, &BenchmarkView::clearSelection, this, &MainWindow::onClearSelection);
    connect(m_benchmarkView, &BenchmarkView::clearAllRows, this, &MainWindow::onClearAllRows);

    connect(ChartViewWidget::getInstance(), &ChartViewWidget::measurementColorChanged,
            [&](int id, QString color) {
                BenchmarkModel::getInstance()->setMeasurementColor(id, color);
            });
}


void MainWindow::onBenchmarkFilter(QString filterText)
{
    QRegExp regExp(filterText, Qt::CaseInsensitive, QRegExp::Wildcard);
    BenchmarkProxyModel::getInstance()->setFilterRegExp(regExp);
}

void MainWindow::onPlotSelection() 
{
	QItemSelectionModel* select = m_benchmarkView->selectionModel();
	if (select->hasSelection()) 
	{
		foreach (QModelIndex idx, select->selectedRows()) 
		{
            auto srcIdx = BenchmarkProxyModel::getInstance()->mapToSource(idx);
            BenchmarkModel::getInstance()->setData(srcIdx, true);
		}
	}
}

void MainWindow::onPlotAllRows() 
{
	m_benchmarkView->selectAll();
	QItemSelectionModel* select = m_benchmarkView->selectionModel();
	if (select->hasSelection()) 
	{
		foreach (QModelIndex idx, select->selectedRows()) 
		{
            auto srcIdx = BenchmarkProxyModel::getInstance()->mapToSource(idx);
            BenchmarkModel::getInstance()->setData(srcIdx, true);
		}
	}
}

void MainWindow::onClearSelection()
{
	QItemSelectionModel* select = m_benchmarkView->selectionModel();
	if (select->hasSelection()) 
	{
		foreach (QModelIndex idx, select->selectedRows()) 
		{
            auto srcIdx = BenchmarkProxyModel::getInstance()->mapToSource(idx);
            BenchmarkModel::getInstance()->setData(srcIdx, false);
		}
	}
}

void MainWindow::onClearAllRows() 
{
	m_benchmarkView->selectAll();
	QItemSelectionModel* select = m_benchmarkView->selectionModel();
	if (select->hasSelection())
	{
		foreach (QModelIndex idx, select->selectedRows()) 
		{
            auto srcIdx = BenchmarkProxyModel::getInstance()->mapToSource(idx);
            BenchmarkModel::getInstance()->setData(srcIdx, false);
		}
	}
}
