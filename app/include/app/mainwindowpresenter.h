#ifndef MAINWINDOW_PRESENTER_H
#define MAINWINDOW_PRESENTER_H

#include <QObject>

class MainWindow;

class MainWindowPresenter : public QObject {
  Q_OBJECT

 public:
  MainWindowPresenter(MainWindow* mainWindow, QObject* parent = nullptr);

  void init();
  void connectActionsToSlots();

 private slots:
  void onOpenFile();
  void onOpenRecentFile();
  void onCloseAllFiles();
  void onCloseFile();
  void onExportChart();
  void onExit();

  void onAboutApp();

 signals:
  void newFileSelected(QString file);

 private:
 private:
  MainWindow* getParentWindow();

  MainWindow* m_mainWindow;
};

#endif
