#pragma once

#include "model/measurement.h"
#include "presenter/presenter_globals.h"

#include <QBarCategoryAxis>
#include <QBarSet>
#include <QObject>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QVXYModelMapper>

QT_CHARTS_USE_NAMESPACE

namespace view {
class ChartView;
}

namespace model {
class BenchmarkModel;
}

namespace presenter {

class ChartPresenter : public QObject {
  Q_OBJECT

 public:
  ChartPresenter(view::ChartView* view, QObject* parent = nullptr);
  ~ChartPresenter() = default;
  void init();
  void setModel(model::BenchmarkModel* model);
  void connectSignalsToSlots();

 public slots:
  void onAddMeasurement(model::Measurement mmt);
  void onRemoveMeasurement(model::Measurement mmt);

 private:
  double calculateMaxY();

 private:
  double m_maxY = 0;
  QBarCategoryAxis* m_axis;
  QBarSeries* m_series;
  view::ChartView* m_view;
  model::BenchmarkModel* m_model;
  QMap<int, QBarSet*> m_barSet;
};

}  // namespace presenter
