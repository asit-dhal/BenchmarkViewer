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
#include "bmcolumns.h"
#include "csvparser.h"
#include "globals.h"
#include "helper.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	qRegisterMetaType<ParserType>("ParserType");
	qRegisterMetaType<Benchmark>("Benchmark");

	m_bmColumns = new BmColumns(this);
	m_worker.moveToThread(&m_workerThread);
	createActions();
	createMenus();
	createWidgets();

	showMaximized();

	m_mainWindowPresenter = new MainWindowPresenter(this, this);
	connectSignalsToSlots();

	m_workerThread.start();
}

MainWindow::~MainWindow() {}

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

void MainWindow::createActions() {
	qCDebug(gui) << "Creating Actions";
	m_openFileAction = new QAction(tr("&Open File(s)"), this);
	m_openFileAction->setShortcuts(QKeySequence::Open);

	m_closeAllFilesAction = new QAction(tr("Close All files"), this);
	m_closeAllFilesAction->setStatusTip(tr("Close All Files "));

	m_exportChart = new QAction(tr("Export Chart"), this);

	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setStatusTip(tr("Exit"));
	m_exitAction->setShortcuts(QKeySequence::Quit);

	m_toogleSelectedFileWidget = new QAction(tr("Toggle selected file widget"), this);
	m_toogleSelectedFileWidget->setStatusTip(tr("Toggle selected file widget"));
	m_toogleSelectedFileWidget->setCheckable(true);
	connect(m_toogleSelectedFileWidget, &QAction::triggered, this, &MainWindow::onToogleSelectedFileWidget);

	for (auto i = 0; i < m_bmColumns->getColumnCount(); i++)
	{
		auto col = m_bmColumns->indexToColumns(i);
		QAction* showColumn = new QAction(m_bmColumns->columnNameToString(col), this);
		showColumn->setCheckable(true);
		showColumn->setChecked(!m_bmColumns->isColumnHidden(col));
		connect(showColumn, &QAction::triggered, this, [=]() {
			if (m_bmColumns->isColumnHidden(col))
			{
				emit m_bmColumns->showColumn(col);
			} 
			else 
			{
				emit m_bmColumns->hideColumn(col);
			}
		});
		m_showColumns.append(showColumn);
	}

	m_aboutApp = new QAction(tr("About BenchmarkViewer"), this);
	m_aboutApp->setStatusTip(tr("About BenchmarkViewer"));
	connect(m_aboutApp, &QAction::triggered, this, &MainWindow::onAboutApp);
}

void MainWindow::updateRecentFileActions(QList<QAction*> recentFileActions)
{
	qDeleteAll(m_openRecentFilesAction);
	m_openRecentFilesAction.clear();

	m_openRecentFilesAction.append(recentFileActions);

	foreach (QAction* recentFileAction, m_openRecentFilesAction)
	{
		m_recentFileMenu->addAction(recentFileAction);
	}
}

void MainWindow::updateCloseFileActions(QList<QAction*> closeFileActions)
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
	qCDebug(gui) << "Creating Menus";
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_openFileAction);
	m_recentFileMenu = m_fileMenu->addMenu(tr("Recent Files"));
	m_closeFileMenu = m_fileMenu->addMenu(tr("Close File(s)"));

	m_fileMenu->addAction(m_closeAllFilesAction);
	m_fileMenu->addAction(m_exportChart);
	m_fileMenu->addAction(m_exitAction);

	m_viewMenu = menuBar()->addMenu(tr("&View"));
	m_viewMenu->addAction(m_toogleSelectedFileWidget);
	m_showColumnsSubMenu = m_viewMenu->addMenu(tr("Columns"));
	m_showColumnsSubMenu->addActions(m_showColumns);

	m_helpMenu = menuBar()->addMenu(tr("&Help"));
	m_helpMenu->addAction(m_aboutApp);
}

void MainWindow::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected) 
{
	// At this moment, we don't do anything
	Q_UNUSED(selected);
	Q_UNUSED(deselected);
}

void MainWindow::createWidgets() {
	qCDebug(gui) << "Creating Widgets";
	m_selectedFilesWidget = new QListWidget();
	m_selectedFilesWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_selectedFilesWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onSelectedFilesWidgetContextMenu(QPoint)));

	QGroupBox* benckmarkSelectorGB = new QGroupBox(tr("Benchmarks"), this);
	m_benchmarkNameFilter = new QLineEdit(this);
	m_benchmarkNameFilter->setPlaceholderText(tr("Filter"));
	m_benchmarkModel = new BenchmarkModel(m_bmColumns, this);
	m_proxyModel = new BenchmarkProxyModel(m_bmColumns, this);
	m_benchmarkView = new BenchmarkView(m_bmColumns, this);
	m_benchmarkDelegate = new BenchmarkDelegate(this);

	m_proxyModel->setSourceModel(m_benchmarkModel);
	m_benchmarkView->setModel(m_proxyModel);
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
	benckmarkSelectorGB->setLayout(benchmarkLayout);

	m_chartView = new ChartViewWidget(this);

	QSplitter* splitter = new QSplitter(this);
	splitter->addWidget(m_selectedFilesWidget);
	splitter->addWidget(benckmarkSelectorGB);
	splitter->addWidget(m_chartView);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 2);
	splitter->setStretchFactor(2, 4);
	setCentralWidget(splitter);

	m_selectedFilesWidget->hide();
	m_toogleSelectedFileWidget->setChecked(m_selectedFilesWidget->isVisible());

	m_selectionModel = new QItemSelectionModel(m_proxyModel);
	m_benchmarkView->setSelectionModel(m_selectionModel);
}

void MainWindow::onSelectedFileDeleted(QString file) 
{
	m_benchmarkModel->removeBenchmark(file);
	m_benchmarkView->resizeColumnsToContents();
}

void MainWindow::connectSignalsToSlots() 
{
	qCDebug(gui) << "Connecting Signals to Slots";
	connect(QCoreApplication::instance(), &QApplication::aboutToQuit, 
		[&]() { m_workerThread.quit();
				m_workerThread.wait(); });

	connect(m_mainWindowPresenter, &MainWindowPresenter::newFileSelected, &m_worker, &Worker::parse);
	connect(m_mainWindowPresenter, &MainWindowPresenter::fileRemoved, this, &MainWindow::selectedFileDeleted);
	connect(&m_worker, &Worker::parsingFinished, this, &MainWindow::onNewBenchmarks);

	connect(this, SIGNAL(selectedFileDeleted(QString)), this, SLOT(onSelectedFileDeleted(QString)));

	connect(m_benchmarkNameFilter, SIGNAL(textChanged(QString)), this, SLOT(onBenchmarkFilter(QString)));

	connect(m_benchmarkModel, &BenchmarkModel::measurementActive, m_chartView, &ChartViewWidget::onAddMeasurement);
	connect(m_benchmarkModel, &BenchmarkModel::measurementInactive, m_chartView, &ChartViewWidget::onRemoveMeasurement);

	connect(m_selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);
	connect(m_benchmarkView, &BenchmarkView::select, this, &MainWindow::onPlotSelection);
	connect(m_benchmarkView, &BenchmarkView::selectAllRows, this, &MainWindow::onPlotAllRows);
	connect(m_benchmarkView, &BenchmarkView::clearSelection, this, &MainWindow::onClearSelection);
	connect(m_benchmarkView, &BenchmarkView::clearAllRows, this, &MainWindow::onClearAllRows);

	connect(m_bmColumns, &BmColumns::showColumn, [this]() { onUpdateColumnStatus(); });
	connect(m_bmColumns, &BmColumns::hideColumn, [this]() { onUpdateColumnStatus(); });

	connect(m_chartView, &ChartViewWidget::measurementColorChanged, [&](int id, QString color) {
		m_benchmarkModel->setMeasurementColor(id, color);
	});
}

void MainWindow::onSelectedFilesWidgetContextMenu(const QPoint& pos)
{
	QPoint globalPos = m_selectedFilesWidget->mapToGlobal(pos);
	QMenu contextMenu;
	contextMenu.addAction(tr("Delete"), this, [this]() {
		for (int i = 0; i < m_selectedFilesWidget->selectedItems().size(); ++i)
		{
			QListWidgetItem* item = m_selectedFilesWidget->takeItem(m_selectedFilesWidget->currentRow());
			emit selectedFileDeleted(item->data(Qt::EditRole).toString());
			delete item;
		}
	});
	contextMenu.exec(globalPos);
}

void MainWindow::onNewBenchmarks(QString filename, Benchmark benchmark)
{
	m_benchmarkModel->addBenchmark(filename, benchmark);
	m_benchmarkView->resizeColumnsToContents();
}

void MainWindow::onToogleSelectedFileWidget() 
{
	if (m_selectedFilesWidget->isVisible())
	{
		m_selectedFilesWidget->hide();
	}
	else
	{
		m_selectedFilesWidget->show();
	}
}

void MainWindow::onBenchmarkFilter(QString filterText)
{
	qCDebug(gui) << "Benchmark filter: " << filterText;
	QRegExp regExp(filterText, Qt::CaseInsensitive, QRegExp::Wildcard);
	m_proxyModel->setFilterRegExp(regExp);
}

void MainWindow::onAboutApp() 
{
	QString text = QString(
      "Benchmark Viewer to plot google microbenchmark data ") +  QChar(0x00A9) + QString(" 2018 Asit Dhal");

	QMessageBox::about(this, tr("About BenchmarkViewer"), text);
}

void MainWindow::onToggleColumnAction()
{
	QAction* act = qobject_cast<QAction*>(sender());
	BmColumns::Columns col = act->data().value<BmColumns::Columns>();
	if (m_bmColumns->isColumnHidden(col))
		emit m_bmColumns->showColumn(col);
	else
		emit m_bmColumns->hideColumn(col);
}

void MainWindow::onUpdateColumnStatus() 
{
	for (auto i = 0; i < m_bmColumns->getColumnCount(); i++)
	{
		auto col = m_bmColumns->indexToColumns(i);
		m_showColumns.at(i)->setChecked(!m_bmColumns->isColumnHidden(col));
	}
}

void MainWindow::onPlotSelection() 
{
	QItemSelectionModel* select = m_benchmarkView->selectionModel();
	if (select->hasSelection()) 
	{
		foreach (QModelIndex idx, select->selectedRows()) 
		{
			auto srcIdx = m_proxyModel->mapToSource(idx);
			qCDebug(gui) << "proxy model index: " << idx << " source model index : " << srcIdx;
			m_benchmarkModel->setData(srcIdx, true);
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
			auto srcIdx = m_proxyModel->mapToSource(idx);
			qCDebug(gui) << "proxy model index: " << idx << " source model index : " << srcIdx;
			m_benchmarkModel->setData(srcIdx, true);
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
			auto srcIdx = m_proxyModel->mapToSource(idx);
			qCDebug(gui) << "proxy model index: " << idx << " source model index : " << srcIdx;
			m_benchmarkModel->setData(srcIdx, false);
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
			auto srcIdx = m_proxyModel->mapToSource(idx);
			qCDebug(gui) << "proxy model index: " << idx << " source model index : " << srcIdx;
			m_benchmarkModel->setData(srcIdx, false);
		}
	}
}
