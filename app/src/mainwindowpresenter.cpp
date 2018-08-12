#include "app/mainwindowpresenter.h"
#include "app/appconfig.h"
#include "app/globals.h"
#include "app/mainwindow.h"
#include "model/abstractparser.h"
#include "model/benchmarkmodel.h"
#include "model/parserfactory.h"
#include "presenter/benchmarkdelegate.h"
#include "presenter/benchmarkproxymodel.h"

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

MainWindowPresenter::MainWindowPresenter(MainWindow* view, QObject* parent)
    : QObject(parent), m_view(view) {}

void MainWindowPresenter::connectActionsToSlots() {
  qCDebug(MAINUI_TAG);
  connect(m_view->getOpenFileAction(), &QAction::triggered, this,
          &MainWindowPresenter::onOpenFile);
  connect(m_view->getCloseAllFilesAction(), &QAction::triggered, this,
          &MainWindowPresenter::onCloseAllFiles);
  connect(m_view->getCloseFileAction(), &QAction::triggered, this,
          &MainWindowPresenter::onCloseFile);
  connect(m_view->getExportChartAction(), &QAction::triggered, this,
          &MainWindowPresenter::onExportChart);

  connect(m_view->getExitAction(), &QAction::triggered, this,
          &MainWindowPresenter::onExit);

  connect(m_view->getAboutApp(), &QAction::triggered, this,
          &MainWindowPresenter::onAboutApp);

  qCDebug(MAINUI_TAG) << "Connecting Signals to slots finished";
}

void MainWindowPresenter::setModel(model::BenchmarkModel* model) {
  m_bmModel = model;

  auto csvParser = model::ParserFactory::getParser(
      model::ParserFactory::ParserType::eCsvParser);
  auto jsonParser = model::ParserFactory::getParser(
      model::ParserFactory::ParserType::eJsonParser);

  qCDebug(MAINUI_TAG) << "connecting CSV Parser signals";
  connect(csvParser.data(), &model::IAbstractParser::parsingFinished,
          [this](QString fileName, model::Measurements mmt) {
            qCDebug(MAINUI_TAG) << "CSV Parsing Finished: " << fileName;
            m_bmModel->addMeasurements(mmt);
          });

  qCDebug(MAINUI_TAG) << "connecting JSON Parser signals";
  connect(jsonParser.data(), &model::IAbstractParser::parsingFinished,
          [this](QString fileName, model::Measurements mmt) {
            qCDebug(MAINUI_TAG) << "JSON Parsing Finished: " << fileName;
            m_bmModel->addMeasurements(mmt);
          });
}

void MainWindowPresenter::onOpenFile() {
  qCDebug(MAINUI_TAG) << "SLOT=> " << Q_FUNC_INFO;
  QString lastPath = appconfig::readLastOpenedFilePath();
  QStringList files =
      QFileDialog::getOpenFileNames(m_view, tr("Open Directory"), lastPath);
  for (auto file : files) {
    if (!file.isEmpty()) {
      appconfig::updateRecentFiles(file);
      model::ParserFactory::getParser(
          model::ParserFactory::ParserType::eJsonParser)
          ->parse(file);
    }
  }

  auto recentFiles = appconfig::readRecentFiles();
  m_view->updateRecentFileActions(recentFiles);
  for (auto action : m_view->getOpenRecentFileActions()) {
    connect(action, &QAction::triggered, this,
            &MainWindowPresenter::onOpenRecentFile);
  }
}

void MainWindowPresenter::onCloseAllFiles() {
  qCDebug(MAINUI_TAG) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onCloseFile() {
  qCDebug(MAINUI_TAG) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onOpenRecentFile() {
  qCDebug(MAINUI_TAG) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onExportChart() {
  qCDebug(MAINUI_TAG) << "SLOT=> " << Q_FUNC_INFO;
}

void MainWindowPresenter::onExit() {
  qCDebug(MAINUI_TAG) << "SLOT=> " << Q_FUNC_INFO;
  QApplication::quit();
}

void MainWindowPresenter::onAboutApp() {
  qCDebug(MAINUI_TAG) << "SLOT=> " << Q_FUNC_INFO;
  QString text = QString::fromUtf8(
      "Benchmark Viewer to plot google microbenchmark data \n\u00A9 2018"
      " Asit Dhal");

  QMessageBox::about(m_view, tr("About BenchmarkViewer"), text);
}

void MainWindowPresenter::init() {
  qCDebug(MAINUI_TAG) << Q_FUNC_INFO;
  connectActionsToSlots();
  m_view->updateRecentFileActions(appconfig::readRecentFiles());
  for (auto action : m_view->getOpenRecentFileActions()) {
    connect(action, &QAction::triggered, this,
            &MainWindowPresenter::onOpenRecentFile);
  }
}
