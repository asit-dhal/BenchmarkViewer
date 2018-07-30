#include "mainwindowpresenter.h"
#include <QAction>
#include <QFileDialog>
#include "appconfig.h"
#include "mainwindow.h"

MainWindowPresenter::MainWindowPresenter(MainWindow* mainWindow,
                                         QObject* parent)
    : QObject(parent), m_mainWindow(mainWindow) {}

void MainWindowPresenter::connectActionsToSlots() {
  connect(m_mainWindow->getOpenFileAction(), &QAction::triggered, this,
          &MainWindowPresenter::onOpenFile);
  connect(m_mainWindow->getCloseAllFilesAction(), &QAction::triggered,
          m_mainWindow, &MainWindow::onCloseAllFiles);
  connect(m_mainWindow->getExportChart(), &QAction::triggered, m_mainWindow,
          &MainWindow::onExportChart);
  connect(m_mainWindow->getExitAction(), &QAction::triggered, m_mainWindow,
          &MainWindow::onExit);
  connect(m_mainWindow->getToogleSelectedFileWidget(), &QAction::triggered,
          m_mainWindow, &MainWindow::onToogleSelectedFileWidget);
  connect(m_mainWindow->getAboutApp(), &QAction::triggered, m_mainWindow,
          &MainWindow::onAboutApp);
}

void MainWindowPresenter::onOpenFile() {
  QString lastPath = appconfig::readLastOpenedFilePath();
  QStringList files = QFileDialog::getOpenFileNames(
      m_mainWindow, tr("Open Directory"), lastPath);
  for (auto file : files) {
    if (!file.isEmpty()) {
      appconfig::updateRecentFiles(file);
      m_mainWindow->updateRecentFileActions();
      emit m_mainWindow->newFileSelected(file);
      updateLastOpenedFilePath(QFileInfo(file).path());
    }
  }
}
