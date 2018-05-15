#ifndef BENCHMARKVIEW_H
#define BENCHMARKVIEW_H

#include <QTableView>
#include "bmcolumns.h"

class BmColumns;
class QHeaderView;

class BenchmarkView : public QTableView {
  Q_OBJECT

 public:
  BenchmarkView(BmColumns* bmColumns, QWidget* parent = 0);
  ~BenchmarkView() = default;

 public slots:
  void onShowColumn(BmColumns::Columns col);
  void onHideColumn(BmColumns::Columns col);

 private slots:
  void onShowHeaderMenu(QPoint p);
  void onSlotMoveLast();
  void onSlotMoveFirst();

 private:
  void updateColumnViewStatus();
  BmColumns* m_bmColumns;
  QHeaderView* m_header;
  QList<QAction*> m_columnShowHideActions;
  QAction* m_moveLastAction;
  QAction* m_moveFirstAction;
  QList<int> m_currentHiddenColumns;
};

#endif  // BENCHMARKVIEW_H
