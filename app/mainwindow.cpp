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
#include "plotconfig.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  m_bmColumns = new BmColumns(this);
  createActions();
  createMenus();
  createWidgets();
  connectSignalsToSlots();
  updateRecentFileActions();
  updateCloseFileActions();
  showMaximized();
}

MainWindow::~MainWindow() {}

void MainWindow::createActions() {
  qCDebug(gui) << "Creating Actions";
  m_openFileAction = new QAction(tr("&Open File(s)"), this);
  m_openFileAction->setShortcuts(QKeySequence::Open);
  connect(m_openFileAction, &QAction::triggered, this, &MainWindow::onOpenFile);

  m_closeAllFilesAction = new QAction(tr("Close All files"), this);
  m_closeAllFilesAction->setStatusTip(tr("Close All Files "));
  connect(m_closeAllFilesAction, &QAction::triggered, this,
          &MainWindow::onCloseAllFiles);

  m_exportChart = new QAction(tr("Export Chart as png"), this);
  connect(m_exportChart, &QAction::triggered, this, &MainWindow::onExportChart);

  m_exitAction = new QAction(tr("E&xit"), this);
  m_exitAction->setStatusTip(tr("Exit"));
  connect(m_exitAction, &QAction::triggered, this, &MainWindow::onExit);

  m_toogleSelectedFileWidget =
      new QAction(tr("Toggle selected file widget"), this);
  m_toogleSelectedFileWidget->setStatusTip(tr("Toggle selected file widget"));
  m_toogleSelectedFileWidget->setCheckable(true);
  connect(m_toogleSelectedFileWidget, &QAction::triggered, this,
          &MainWindow::onToogleSelectedFileWidget);

  for (auto i = 0; i < m_bmColumns->getColumnCount(); i++) {
    auto col = m_bmColumns->indexToColumns(i);
    QAction* showColumn =
        new QAction(m_bmColumns->columnNameToString(col), this);
    showColumn->setCheckable(true);
    showColumn->setChecked(!m_bmColumns->isColumnHidden(col));
    connect(showColumn, &QAction::triggered, this, [=]() {
      if (m_bmColumns->isColumnHidden(col)) {
        emit m_bmColumns->showColumn(col);
      } else {
        emit m_bmColumns->hideColumn(col);
      }
    });
    m_showColumns.append(showColumn);
  }

  m_aboutApp = new QAction(tr("About BenchmarkViewer"), this);
  m_aboutApp->setStatusTip(tr("About BenchmarkViewer"));
  connect(m_aboutApp, &QAction::triggered, this, &MainWindow::onAboutApp);
}

void MainWindow::updateRecentFileActions() {
  qDeleteAll(m_openRecentFilesAction);
  m_openRecentFilesAction.clear();

  QStringList recentFiles = readRecentFiles();
  qCDebug(gui) << "Recent Files: " << recentFiles.size() << "->" << recentFiles;
  int i = 1;
  foreach (QString recentFile, recentFiles) {
    if (recentFile.isEmpty())
      continue;
    QString text = tr("&%1 %2").arg(i).arg(QFileInfo(recentFile).fileName());
    QAction* recentFileAction = new QAction(text, this);
    recentFileAction->setData(recentFile);
    recentFileAction->setVisible(true);
    connect(recentFileAction, &QAction::triggered,
            [ this, _recentFile = recentFile ]() {
              updateRecentFiles(_recentFile);
              updateRecentFileActions();
              emit newFileSelected(_recentFile);
            });
    i++;
    m_openRecentFilesAction.append(recentFileAction);
  }

  foreach (QAction* recentFileAction, m_openRecentFilesAction) {
    m_recentFileMenu->addAction(recentFileAction);
  }
}

void MainWindow::updateCloseFileActions() {
  qDeleteAll(m_closeFileActions);
  m_closeFileActions.clear();

  int i = 1;
  foreach (QString openedFile, m_files) {
    if (openedFile.isEmpty())
      continue;
    QString text = tr("&%1 %2").arg(i).arg(QFileInfo(openedFile).fileName());
    QAction* closeFileAction = new QAction(text, this);
    closeFileAction->setData(openedFile);
    closeFileAction->setVisible(true);
    connect(closeFileAction, &QAction::triggered,
            [ this, _closeFile = openedFile ]() {
              emit selectedFileDeleted(_closeFile);
            });
    i++;
    m_closeFileActions.append(closeFileAction);
  }

  foreach (QAction* closeFileAction, m_closeFileActions) {
    m_closeFileMenu->addAction(closeFileAction);
  }
}

void MainWindow::createMenus() {
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

void MainWindow::onSelectionChanged(const QItemSelection& selected,
                                    const QItemSelection& deselected) {
  Q_UNUSED(selected);
  Q_UNUSED(deselected);
  //  qCDebug(mainWindow) << "new selected: " << selected;
  //  qCDebug(mainWindow) << "deselected: " << deselected;
}

void MainWindow::onOpenFile() {
  QStringList files =
      QFileDialog::getOpenFileNames(this, tr("Open Directory"), "/home");
  for (auto file : files) {
    if (!file.isEmpty()) {
      updateRecentFiles(file);
      updateRecentFileActions();
      emit newFileSelected(file);
    }
  }
}

void MainWindow::onCloseFile(QString filename) {
  onSelectedFileDeleted(filename);
  qCDebug(gui) << "closing file";
}

void MainWindow::onCloseAllFiles() {
  for (auto file : m_files) {
    onSelectedFileDeleted(file);
  }
}

void MainWindow::onExportChart() {
  QPixmap pixmap = m_chartView->grab();
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save Chart as png"), "", tr("images (*.png);;All Files (*)"));
  if (!fileName.isEmpty())
    pixmap.save(fileName, "PNG");
}

void MainWindow::onExit() {
  qCDebug(gui) << "closing application";
  QApplication::quit();
}

void MainWindow::createWidgets() {
  qCDebug(gui) << "Creating Widgets";
  m_selectedFilesWidget = new QListWidget();
  m_selectedFilesWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(m_selectedFilesWidget, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(onSelectedFilesWidgetContextMenu(QPoint)));

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
  m_plotConfigWidget = new PlotConfig(m_bmColumns, this);
  benchmarkLayout->addWidget(m_plotConfigWidget);
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

void MainWindow::onNewFileSelected(QString file) {
  m_files.push(file);
  m_selectedFilesWidget->addItem(file);
  QFileInfo fi(file);
  if (fi.suffix().compare("json", Qt::CaseInsensitive) == 0) {
    qCDebug(gui) << "JSON File";
    m_parser = new JsonParser(this);
  } else if (fi.suffix().compare("csv", Qt::CaseInsensitive) == 0) {
    qCDebug(gui) << "CSV File";
    m_parser = new CsvParser(this);
  } else {
    qCDebug(gui) << "Invalid file: " << file;
  }
  // to be multithreaded
  connect(m_parser, SIGNAL(parsingFinished(QString, Benchmark)), this,
          SLOT(onNewBenchmarks(QString, Benchmark)));
  m_parser->parse(file);
  m_parser->deleteLater();
}

void MainWindow::onSelectedFileDeleted(QString file) {
  m_files.removeOne(file);
  m_benchmarkModel->removeBenchmark(file);
  m_benchmarkView->resizeColumnsToContents();
}

void MainWindow::connectSignalsToSlots() {
  qCDebug(gui) << "Connecting Signals to Slots";
  connect(this, SIGNAL(newFileSelected(QString)), this,
          SLOT(onNewFileSelected(QString)));

  connect(this, &MainWindow::newFileSelected, this,
          [this](QString) { updateCloseFileActions(); });
  connect(this, SIGNAL(selectedFileDeleted(QString)), this,
          SLOT(onSelectedFileDeleted(QString)));

  connect(m_benchmarkNameFilter, SIGNAL(textChanged(QString)), this,
          SLOT(onBenchmarkFilter(QString)));

  connect(m_benchmarkModel, &BenchmarkModel::measurementActive, m_chartView,
          &ChartViewWidget::onAddMeasurement);
  connect(m_benchmarkModel, &BenchmarkModel::measurementInactive, m_chartView,
          &ChartViewWidget::onRemoveMeasurement);

  connect(m_selectionModel, &QItemSelectionModel::selectionChanged, this,
          &MainWindow::onSelectionChanged);
  connect(m_benchmarkView, &BenchmarkView::select, this,
          &MainWindow::onPlotSelection);
  connect(m_benchmarkView, &BenchmarkView::selectAllRows, this,
          &MainWindow::onPlotAllRows);
  connect(m_benchmarkView, &BenchmarkView::clearSelection, this,
          &MainWindow::onClearSelection);
  connect(m_benchmarkView, &BenchmarkView::clearAllRows, this,
          &MainWindow::onClearAllRows);

  connect(m_bmColumns, &BmColumns::showColumn,
          [this]() { onUpdateColumnStatus(); });
  connect(m_bmColumns, &BmColumns::hideColumn,
          [this]() { onUpdateColumnStatus(); });
}

void MainWindow::onSelectedFilesWidgetContextMenu(const QPoint& pos) {
  QPoint globalPos = m_selectedFilesWidget->mapToGlobal(pos);
  QMenu contextMenu;
  contextMenu.addAction(tr("Delete"), this, [this]() {
    for (int i = 0; i < m_selectedFilesWidget->selectedItems().size(); ++i) {
      QListWidgetItem* item =
          m_selectedFilesWidget->takeItem(m_selectedFilesWidget->currentRow());
      emit selectedFileDeleted(item->data(Qt::EditRole).toString());
      delete item;
    }
  });
  contextMenu.exec(globalPos);
}

void MainWindow::onNewBenchmarks(QString filename, Benchmark benchmark) {
  m_benchmarkModel->addBenchmark(filename, benchmark);
  m_benchmarkView->resizeColumnsToContents();
}

void MainWindow::onToogleSelectedFileWidget() {
  if (m_selectedFilesWidget->isVisible()) {
    m_selectedFilesWidget->hide();
  } else {
    m_selectedFilesWidget->show();
  }
}

void MainWindow::onBenchmarkFilter(QString filterText) {
  qCDebug(gui) << "Benchmark filter: " << filterText;
  QRegExp regExp(filterText, Qt::CaseInsensitive, QRegExp::Wildcard);
  m_proxyModel->setFilterRegExp(regExp);
}

void MainWindow::onAboutApp() {
  QString text = QString::fromUtf8(
      "Benchmark Viewer to plot google microbenchmark data \n\u00A9 2018"
      " Asit Dhal");

  QMessageBox::about(this, tr("About BenchmarkViewer"), text);
}

void MainWindow::onToggleColumnAction() {
  QAction* act = qobject_cast<QAction*>(sender());
  BmColumns::Columns col = act->data().value<BmColumns::Columns>();
  if (m_bmColumns->isColumnHidden(col))
    emit m_bmColumns->showColumn(col);
  else
    emit m_bmColumns->hideColumn(col);
}

void MainWindow::onUpdateColumnStatus() {
  for (auto i = 0; i < m_bmColumns->getColumnCount(); i++) {
    auto col = m_bmColumns->indexToColumns(i);
    m_showColumns.at(i)->setChecked(!m_bmColumns->isColumnHidden(col));
  }
}

void MainWindow::onPlotSelection() {
  QItemSelectionModel* select = m_benchmarkView->selectionModel();
  if (select->hasSelection()) {
    foreach (QModelIndex idx, select->selectedRows()) {
      auto srcIdx = m_proxyModel->mapToSource(idx);
      qCDebug(gui) << "proxy model index: " << idx
                   << " source model index : " << srcIdx;
      m_benchmarkModel->setData(srcIdx, true);
    }
  }
}

void MainWindow::onPlotAllRows() {
  m_benchmarkView->selectAll();
  QItemSelectionModel* select = m_benchmarkView->selectionModel();
  if (select->hasSelection()) {
    foreach (QModelIndex idx, select->selectedRows()) {
      auto srcIdx = m_proxyModel->mapToSource(idx);
      qCDebug(gui) << "proxy model index: " << idx
                   << " source model index : " << srcIdx;
      m_benchmarkModel->setData(srcIdx, true);
    }
  }
}

void MainWindow::onClearSelection() {
  QItemSelectionModel* select = m_benchmarkView->selectionModel();
  if (select->hasSelection()) {
    foreach (QModelIndex idx, select->selectedRows()) {
      auto srcIdx = m_proxyModel->mapToSource(idx);
      qCDebug(gui) << "proxy model index: " << idx
                   << " source model index : " << srcIdx;
      m_benchmarkModel->setData(srcIdx, false);
    }
  }
}

void MainWindow::onClearAllRows() {
  m_benchmarkView->selectAll();
  QItemSelectionModel* select = m_benchmarkView->selectionModel();
  if (select->hasSelection()) {
    foreach (QModelIndex idx, select->selectedRows()) {
      auto srcIdx = m_proxyModel->mapToSource(idx);
      qCDebug(gui) << "proxy model index: " << idx
                   << " source model index : " << srcIdx;
      m_benchmarkModel->setData(srcIdx, false);
    }
  }
}
