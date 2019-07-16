#include "mainwindow_presenter.h"
#include "mainwindow.h"
#include "appconfig.h"
#include "globals.h"
#include "helper.h"
#include "benchmarkmodel.h"

MainWindowPresenter::MainWindowPresenter(MainWindow* mainWindow, QObject* parent): QObject(parent), m_view(mainWindow)
{
	m_worker.moveToThread(&m_workerThread);
	m_workerThread.start();
	
	connect(QCoreApplication::instance(), &QApplication::aboutToQuit,
		[&]() { m_workerThread.quit();
				m_workerThread.wait(); });

	connectSignalsToSlots();
	updateRecentFilesActions();
}

void MainWindowPresenter::connectSignalsToSlots()
{
	connect(this, &MainWindowPresenter::newFileSelected, &m_worker, &Worker::parse);
	connect(&m_worker, &Worker::parsingFinished, this, &MainWindowPresenter::onNewBenchmark);
	connect(this, &MainWindowPresenter::fileRemoved, this, &MainWindowPresenter::onRemoveBenchmark);

	connect(m_view->getOpenFileAction(), &QAction::triggered, this, &MainWindowPresenter::onOpenFileTriggered);
	connect(m_view->getCloseAllFilesAction(), &QAction::triggered, this, &MainWindowPresenter::onCloseAllFilesTriggered);
	connect(m_view->getExportChartAction(), &QAction::triggered, this, &MainWindowPresenter::onExportChartTriggered);
	connect(m_view->getExitAction(), &QAction::triggered, this, &MainWindowPresenter::onExitTriggered);
	connect(m_view->getAboutBenchmarkAppAction(), &QAction::triggered, this, &MainWindowPresenter::onAboutAppTriggered);
}

void MainWindowPresenter::onOpenFileTriggered()
{
	QString lastPath = readLastOpenedFilePath();
	QStringList files = QFileDialog::getOpenFileNames(m_view, tr("Open Directory"), lastPath);
	for (auto file : files)
	{
		openFile(file);
	}
}

void MainWindowPresenter::onCloseAllFilesTriggered()
{
	for (auto file : m_openedFiles)
	{
		closeFile(file);
	}
}

void MainWindowPresenter::onExportChartTriggered()
{
    QString lastPath = readLastExportedFilePath();
    QString filename = QFileDialog::getSaveFileName(m_view, tr("Save Chart"), lastPath, tr("png file (*.png)"));
    updateLastExportedFilePath(QFileInfo(filename).path());
	if (!m_view->getChartViewWidget()->exportChart(filename))
	{
		qCCritical(gui) << "Export failed";
	}
}

void MainWindowPresenter::onExitTriggered()
{
	qCDebug(gui) << "closing application";
	QApplication::quit();
}

void MainWindowPresenter::onAboutAppTriggered()
{
	QString text = QString(
		"Benchmark Viewer to plot google microbenchmark data ") + QChar(0x00A9) + QString(" 2018 Asit Dhal");

	QMessageBox::about(m_view, tr("About BenchmarkViewer"), text);
}

void MainWindowPresenter::onNewBenchmark(QString filename, Benchmark benchmark)
{
    BenchmarkModel::getInstance()->addBenchmark(filename, benchmark);
	//m_benchmarkView->resizeColumnsToContents();
}

void MainWindowPresenter::onRemoveBenchmark(QString filename)
{
    BenchmarkModel::getInstance()->removeBenchmark(filename);
	//m_benchmarkView->resizeColumnsToContents();
}


void MainWindowPresenter::openFile(QString filename)
{
	if (!filename.isEmpty())
	{
		updateRecentFiles(filename);
		updateRecentFilesActions();

		emit newFileSelected(Helper::getParserTypeFromFilename(filename), filename);
		
		updateLastOpenedFilePath(QFileInfo(filename).path());
		m_openedFiles.append(filename);
		updateCloseFileActions();
	}
}

void MainWindowPresenter::closeFile(QString filename)
{
	if (!filename.isEmpty())
	{
		emit fileRemoved(filename);
		m_openedFiles.removeOne(filename);
		updateCloseFileActions();
	}
}

void MainWindowPresenter::updateRecentFilesActions()
{
	QList<QAction*> recentFileActions;
	QStringList recentFiles = readRecentFiles();
	qCDebug(gui) << "Recent Files: " << recentFiles.size() << "->" << recentFiles;
	int i = 1;
	foreach(QString recentFile, recentFiles)
	{
		if (recentFile.isEmpty())
			continue;
		QString text = tr("&%1 %2").arg(i).arg(QFileInfo(recentFile).fileName());
		QAction* recentFileAction = new QAction(text, m_view);
		recentFileAction->setData(recentFile);
		recentFileAction->setVisible(true);
		connect(recentFileAction, &QAction::triggered, [this, _recentFile = recentFile]() {
			openFile(_recentFile);
		});
		i++;
		recentFileActions.append(recentFileAction);
	}
	m_view->setRecentFileActions(recentFileActions);
}

void MainWindowPresenter::updateCloseFileActions()
{
	QList<QAction*> closeFileActions;
	int i = 1;
	foreach(QString openedFile, m_openedFiles)
	{
		if (openedFile.isEmpty())
			continue;
		QString text = tr("&%1 %2").arg(i).arg(QFileInfo(openedFile).fileName());
		QAction* closeFileAction = new QAction(text, m_view);
		closeFileAction->setData(openedFile);
		closeFileAction->setVisible(true);
		connect(closeFileAction, &QAction::triggered,
			[this, _closeFile = openedFile]() {
				closeFile(_closeFile);
		});
		i++;
		closeFileActions.append(closeFileAction);
	}

	m_view->setCloseFileActions(closeFileActions);
}
