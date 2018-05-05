#ifndef BENCHMARKVIEW_H
#define BENCHMARKVIEW_H

#include <QLoggingCategory>
#include <QTableView>

Q_DECLARE_LOGGING_CATEGORY(benchmarkView);

class QHeaderView;

class BenchmarkView : public QTableView {
  Q_OBJECT

 public:
  BenchmarkView(QWidget* parent = 0);
  ~BenchmarkView() = default;

 private slots:
  void onShowHeaderMenu(QPoint p);
  void onSlotHideColumn();
  void onShowHiddenColumn();
  void onSlotMoveLast();
  void onSlotMoveFirst();

 private:
  QHeaderView* m_header;
  QAction* m_hideAction;
  QAction* m_moveLastAction;
  QAction* m_moveFirstAction;

  QList<int> m_currentHiddenColumns;
};

#endif  // BENCHMARKVIEW_H
