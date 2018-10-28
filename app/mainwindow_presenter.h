#pragma once

#include <QObject>
#include <QWidget>
#include <QStringList>
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

signals:
	void newFileSelected(ParserType, QString);
	void fileRemoved(QString);

private:
	void connectSignalsToSlots();
	void updateRecentFilesActions();
	void updateCloseFileActions();
	void openFile(QString filename);
	void closeFile(QString filename);

	MainWindow* m_view;
	QStringList m_openedFiles;
};