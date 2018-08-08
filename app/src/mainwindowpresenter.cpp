#include "app/mainwindowpresenter.h"
#include "app/appconfig.h"
#include "app/globals.h"
#include "app/mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

MainWindowPresenter::MainWindowPresenter(MainWindow* mainWindow,
                                         QObject* parent)
    : QObject(parent), m_mainWindow(mainWindow) {}

void MainWindowPresenter::connectActionsToSlots() {
  connect(m_mainWindow->getOpenFileAction(), &QAction::triggered, this,
          &MainWindowPresenter::onOpenFile);
  connect(m_mainWindow->getRecentFilesAction(), &QAction::triggered, this,
          &MainWindowPresenter::onRecentFiles);
  connect(m_mainWindow->getCloseAllFilesAction(), &QAction::triggered, this,
          &MainWindowPresenter::onCloseAllFiles);
  connect(m_mainWindow->getCloseFileAction(), &QAction::triggered, this,
          &MainWindowPresenter::onCloseFile);
  connect(m_mainWindow->getExportChartAction(), &QAction::triggered, this,
          &MainWindowPresenter::onExportChart);

  connect(m_mainWindow->getExitAction(), &QAction::triggered, this,
          &MainWindowPresenter::onExit);

  connect(m_mainWindow->getAboutApp(), &QAction::triggered, this,
          &MainWindowPresenter::onAboutApp);
  //  m_mainWindow,
  //          &MainWindow::onExit);
  //  connect(m_mainWindow->getToogleSelectedFileWidget(),
  //  &QAction::triggered,
  //          m_mainWindow, &MainWindow::onToogleSelectedFileWidget);
  //  connect(m_mainWindow->getAboutApp(), &QAction::triggered, m_mainWindow,
  //          &MainWindow::onAboutApp);
}

void MainWindowPresenter::onOpenFile() {
  qCDebug(mainui) << "SLOT=> " << Q_FUNC_INFO;
  QString lastPath = appconfig::readLastOpenedFilePath();
  QStringList files = QFileDialog::getOpenFileNames(
      m_mainWindow, tr("Open Directory"), lastPath);
  for (auto file : files) {
    if (!file.isEmpty()) {
      appconfig::updateRecentFiles(file);
      // m_mainWindow->updateRecentFileActions();
      //      emit m_mainWindow->newFileSelected(file);
      //      updateLastOpenedFilePath(QFileInfo(file).path());
    }
  }
}

void MainWindowPresenter::onCloseAllFiles() {
  qCDebug(mainui) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onCloseFile() {
  qCDebug(mainui) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onRecentFiles() {
  qCDebug(mainui) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onExportChart() {
  qCDebug(mainui) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onExit() {
  qCDebug(mainui) << "SLOT=> " << Q_FUNC_INFO;
  QApplication::quit();
}

void MainWindowPresenter::onAboutApp() {
  qCDebug(mainui) << "SLOT=> " << Q_FUNC_INFO;
  QString text = QString::fromUtf8(
      "Benchmark Viewer to plot google microbenchmark data \n\u00A9 2018"
      " Asit Dhal");

  QMessageBox::about(getParentWindow(), tr("About BenchmarkViewer"), text);
}

MainWindow* MainWindowPresenter::getParentWindow() {
  return m_mainWindow;
}
