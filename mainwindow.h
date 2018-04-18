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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QPoint>
#include <QStack>
#include "benchmark.h"
#include "parser.h"

class QMenu;
class QAction;
class QListWidget;
class QFileSystemModel;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = 0);
  ~MainWindow();

 signals:
  void newFileSelected(QString);
  void selectedFileDeleted(QString);

 private:
  void createActions();
  void createMenus();
  void createWidgets();
  void connectSignalsToSlots();

 public slots:
  void onNewBenchmarks(QString filename, Benchmark benchmark);

 private slots:
  void onOpenFile();
  void onCloseFile();
  void onCloseAllFiles();
  void onCloseAllFilesExceptSelected();
  void onExit();
  void onNewFileSelected(QString file);
  void onSelectedFilesWidgetContextMenu(const QPoint& pos);
  void onSelectedFileDeleted(QString file);

 private:
  QMenu* m_fileMenu;
  QMenu* m_viewMenu;
  QMenu* m_helpMenu;

  QAction* m_openFileAction;
  QAction* m_recentFilesAction;
  QAction* m_closeFileAction;
  QAction* m_closeAllFilesAction;
  QAction* m_closeAllFilesExceptSelectedAction;
  QAction* m_exitAction;

  QStack<QString> m_files;
  QListWidget* m_selectedFilesWidget;
  QMap<QString, Benchmark> m_benchmarks;
  Parser* m_parser;
};

#endif  // MAINWINDOW_H
