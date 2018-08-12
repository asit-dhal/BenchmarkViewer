#ifndef MAINWINDOW_PRESENTER_H
#define MAINWINDOW_PRESENTER_H

#include <QObject>

class MainWindow;

namespace model {
class BenchmarkModel;
class ColumnModel;
}  // namespace model

namespace presenter {
class BenchmarkProxyModel;
class BenchmarkDelegate;
}  // namespace presenter

class MainWindowPresenter : public QObject {
  Q_OBJECT

 public:
  MainWindowPresenter(MainWindow* view, QObject* parent = nullptr);
  void setModel(model::BenchmarkModel* model);
  void init();

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
  void connectActionsToSlots();

 private:
  MainWindow* m_view;
  model::BenchmarkModel* m_bmModel;
};  // namespace modelclassMainWindowPresenter:publicQObject

#endif
