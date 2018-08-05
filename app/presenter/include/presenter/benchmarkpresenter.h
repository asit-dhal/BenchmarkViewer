#ifndef BENCHMARK_PRESENTER_H
#define BENCHMARK_PRESENTER_H

#include <QObject>

namespace view {
class BenchmarkView;
}

namespace presenter {

class BenchmarkPresenter : public QObject {
public:
  BenchmarkPresenter(view::BenchmarkView *view, QObject *parent=nullptr);

public slots:
 void onShowColumn(int colIdx);
 void onHideColumn(int colIdx);

private slots:
  void onContextMenuOnHeader(QPoint p);
  void onContextMenuOnBody(QPoint p);
  void onSlotMoveLast();
  void onSlotMoveFirst();


private:
    view::BenchmarkView *m_view;
};

}

#endif
