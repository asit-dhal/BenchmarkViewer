#ifndef BENCHMARK_PRESENTER_H
#define BENCHMARK_PRESENTER_H

#include <QObject>

namespace view {
class BenchmarkView;
}

class QAbstractItemModel;

namespace presenter {

class BenchmarkDelegate;
class BenchmarkProxyModel;

class BenchmarkPresenter : public QObject {
 public:
  BenchmarkPresenter(view::BenchmarkView* view = nullptr,
                     QObject* parent = nullptr);
  void init();
  bool setModel(QAbstractItemModel* model);
  void setProxyFilter(QString filterText);

 public slots:
  void onShowColumn(int colIdx);
  void onHideColumn(int colIdx);

 private slots:
  void onContextMenuOnHeader(QPoint p);
  void onContextMenuOnBody(QPoint p);
  void onSlotMoveLast();
  void onSlotMoveFirst();

 private:
  void connectSignalsToSlots();

 private:
  view::BenchmarkView* m_view;
  QAbstractItemModel* m_model;
  BenchmarkDelegate* m_delegate;
  BenchmarkProxyModel* m_proxyModel;
};

}  // namespace presenter

#endif
