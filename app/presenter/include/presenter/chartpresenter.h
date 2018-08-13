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

class ChartProxyModel;

class ChartPresenter : public QObject {
  Q_OBJECT

 public:
  ChartPresenter(view::ChartView* view, QObject* parent = nullptr);
  ~ChartPresenter() = default;
  void init();
  void update();
  void setModel(model::BenchmarkModel* model);
  void connectSignalsToSlots();

 public slots:
  void onAddMeasurement(model::Measurement mmt);
  void onRemoveMeasurement(model::Measurement mmt);
  void onAddMeasurementAttr(model::Measurement::Attributes attr);
  void onRemoveMeasurementAttr(model::Measurement::Attributes attr);

 private:
  double calculateMaxY();

 private:
  double m_maxY = 0;
  QBarCategoryAxis* m_axis;
  QBarSeries* m_series;
  view::ChartView* m_view;
  model::BenchmarkModel* m_model;
  ChartProxyModel* m_proxyModel;
  QMap<int, QBarSet*> m_barSet;
  QList<model::Measurement::Attributes> m_xAxisAttributes;
};

}  // namespace presenter
