#ifndef MAINWINDOW_PRESENTER_H
#define MAINWINDOW_PRESENTER_H

#include <QObject>

class MainWindow;

class MainWindowPresenter : public QObject {
  Q_OBJECT

 public:
  MainWindowPresenter(MainWindow* mainWindow, QObject* parent = nullptr);
  void connectActionsToSlots();

 private slots:
  void onOpenFile();
  void onRecentFiles();
  void onCloseAllFiles();
  void onCloseFile();
  void onExportChart();
  void onExit();

  void onAboutApp();

 private:
 private:
  MainWindow* getParentWindow();

  MainWindow* m_mainWindow;
};

#endif
