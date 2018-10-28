#pragma once

#include <QObject>
#include <QWidget>
#include <QStringList>
#include "worker.h"
#include <QThread>
#include "abstractparser.h"

class MainWindow;

class MainWindowPresenter: public QObject
{
	Q_OBJECT
public:
	MainWindowPresenter(MainWindow* mainWindow, QObject* parent);

public slots:
	void onOpenFileTriggered();
	void onCloseAllFilesTriggered();
	void onExportChartTriggered();
	void onExitTriggered();
	void onAboutAppTriggered();
	void onNewBenchmark(QString filename, Benchmark benchmark);
	void onRemoveBenchmark(QString filename);

signals:
	void newFileSelected(ParserType, QString);
	void fileRemoved(QString);

private:
	void connectSignalsToSlots();
	void updateRecentFilesActions();
	void updateCloseFileActions();
	void openFile(QString filename);
	void closeFile(QString filename);

	Worker m_worker;
	QThread m_workerThread;
	MainWindow* m_view;
	QStringList m_openedFiles;
};