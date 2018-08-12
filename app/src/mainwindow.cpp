/*=========================================================================

   Program: QCommander

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   QCommander is a free software; you can redistribute it and/or modify it.


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

#include "app/mainwindow.h"
#include "app/globals.h"
#include "app/mainwindowpresenter.h"
#include "app/ui_mainwindow.h"
#include "model/benchmarkmodel.h"
#include "model/measurement.h"
#include "view/benchmarkview.h"

#include <QFileInfo>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  createBenchmarkView();
  createModels();
  createPresenter();
  qCDebug(MAINUI_TAG) << "Construction Finished";
}

MainWindow::~MainWindow() {
  delete ui;
}

QAction* MainWindow::getOpenFileAction() {
  return ui->actionOpen_File_s;
}

QVector<QAction*> MainWindow::getOpenRecentFileActions() {
  return m_recentFileActions;
}

QVector<QAction*> MainWindow::getColumnVisibilityActions() {
  return m_columnVisibilityActions;
}

QAction* MainWindow::getCloseFileAction() {
  return ui->actionClose_File;
}

QAction* MainWindow::getCloseAllFilesAction() {
  return ui->actionClose_All_Files;
}

QAction* MainWindow::getExportChartAction() {
  return ui->actionExport_Chart;
}

QAction* MainWindow::getExitAction() {
  return ui->actionExit;
}

QAction* MainWindow::getAboutApp() {
  return ui->actionAbout_BenchmarkViewer;
}

void MainWindow::updateRecentFileActions(QStringList recentFiles) {
  qDeleteAll(m_recentFileActions);
  m_recentFileActions.clear();
  qCDebug(MAINUI_TAG) << "Recent Files: " << recentFiles.size() << "->"
                      << recentFiles;
  int i = 1;
  foreach (QString recentFile, recentFiles) {
    if (recentFile.isEmpty())
      continue;
    QString text = tr("&%1 %2").arg(i).arg(QFileInfo(recentFile).fileName());
    QAction* recentFileAction = new QAction(text, this);
    recentFileAction->setData(recentFile);
    recentFileAction->setVisible(true);
    i++;
    m_recentFileActions.append(recentFileAction);
  }

  foreach (QAction* recentFileAction, m_recentFileActions) {
    ui->menuRecent_Files->addAction(recentFileAction);
  }
}

void MainWindow::createBenchmarkView() {
  qCDebug(MAINUI_TAG);
  // QGroupBox* benckmarkSelectorGB = new QGroupBox(tr("Benchmarks"), this);
  m_filter = new QLineEdit(this);
  m_filter->setPlaceholderText(tr("Filter"));
  m_benchmarkView = new view::BenchmarkView(this);

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(m_filter);
  layout->addWidget(m_benchmarkView);
  // benckmarkSelectorGB->setLayout(layout);

  // ui->
  ui->centralWidget->setLayout(layout);
  qCDebug(MAINUI_TAG) << "Creating BenchmarkView Finished";
}

void MainWindow::createPresenter() {
  qCDebug(MAINUI_TAG);
  m_presenter = new MainWindowPresenter(this);
  qCDebug(MAINUI_TAG) << "Creating Presenter Finished";
}

void MainWindow::createModels() {
  qCDebug(MAINUI_TAG);
  m_bmModel = new model::BenchmarkModel(this);

  qCDebug(MAINUI_TAG) << "Creating Model Finished";
}

void MainWindow::init() {
  qCDebug(MAINUI_TAG);
  m_benchmarkView->init();
  m_benchmarkView->setBenchmarkModel(m_bmModel);
  m_presenter->init();
  m_presenter->setModel(m_bmModel);

  foreach (QAction* act, m_columnVisibilityActions) {
    auto attr = act->data().value<model::Measurement::Attributes>();
    if (attr == model::Measurement::Attributes::eCpuTime ||
        attr == model::Measurement::Attributes::eRealTime ||
        attr == model::Measurement::Attributes::eName) {
      qCDebug(MAINUI_TAG) << "Enabling default Col attributes";
      act->trigger();
    }
  }
  qCDebug(MAINUI_TAG) << "Initialization Finished";
}

void MainWindow::closeEvent(QCloseEvent*) {
  ui->actionExit->trigger();
}

view::BenchmarkView* MainWindow::getBenchmarkView() const {
  return m_benchmarkView;
}

void MainWindow::updateViewColumnMenus(
    QMap<model::Measurement::Attributes, bool> colVisibility) {
  qDeleteAll(m_columnVisibilityActions);
  m_columnVisibilityActions.clear();
  auto colNames = model::Measurement::getAttributeNames();
  for (auto it = colVisibility.begin(); it != colVisibility.end(); it++) {
    qCDebug(MAINUI_TAG)
        << QString("%1 => %2").arg(colNames[it.key()]).arg(it.value());
  }

  for (auto it = colVisibility.begin(); it != colVisibility.end(); it++) {
    QAction* toggleVisibility = new QAction(colNames[it.key()], this);
    toggleVisibility->setCheckable(true);
    toggleVisibility->setVisible(true);
    toggleVisibility->setChecked(it.value());
    toggleVisibility->setData(QVariant::fromValue(it.key()));
    m_columnVisibilityActions.append(toggleVisibility);
  }

  foreach (QAction* toggleVisibility, m_columnVisibilityActions) {
    ui->menuColumns->addAction(toggleVisibility);
  }
}

QLineEdit* MainWindow::getBenchmarkFilterWidget() {
  return m_filter;
}
