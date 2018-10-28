#include "mainwindow_presenter.h"
#include "mainwindow.h"
#include "appconfig.h"
#include "globals.h"
#include "helper.h"

MainWindowPresenter::MainWindowPresenter(MainWindow* mainWindow, QObject* parent): QObject(parent), m_view(mainWindow)
{
	connectSignalsToSlots();

	updateRecentFilesActions();
}

void MainWindowPresenter::connectSignalsToSlots()
{
	connect(m_view->getOpenFileAction(), &QAction::triggered, this, &MainWindowPresenter::onOpenFileTriggered);
	connect(m_view->getCloseAllFilesAction(), &QAction::triggered, this, &MainWindowPresenter::onCloseAllFilesTriggered);
	connect(m_view->getExportChartAction(), &QAction::triggered, this, &MainWindowPresenter::onExportChartTriggered);
	connect(m_view->getExitAction(), &QAction::triggered, this, &MainWindowPresenter::onExitTriggered);
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
	//QPixmap pixmap = m_chartView->grab();
	QString fileName = QFileDialog::getSaveFileName(m_view, tr("Save Chart"), "", tr("png file (*.png)"));
	// delegate grab view  to chart
	//if (!fileName.isEmpty())
	//	pixmap.save(fileName, "PNG");
}

void MainWindowPresenter::onExitTriggered()
{
	qCDebug(gui) << "closing application";
	QApplication::quit();
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
	m_view->updateRecentFileActions(recentFileActions);
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

	m_view->updateCloseFileActions(closeFileActions);
}