#include "presenter/chartpresenter.h"
#include "model/benchmarkmodel.h"
#include "view/chartview.h"

namespace presenter {

ChartPresenter::ChartPresenter(view::ChartView* view, QObject* parent)
    : QObject(parent), m_view(view) {
  m_series = new QBarSeries;
  m_axis = new QBarCategoryAxis();
}

void ChartPresenter::init() {
  m_view->getChart()->addSeries(m_series);
  m_view->getChart()->legend()->setVisible(true);
  m_view->getChart()->legend()->setAlignment(Qt::AlignRight);

  QStringList categories;
  categories << "CPU Time"
             << "Real Time";
  m_axis->append(categories);
  m_view->getChart()->createDefaultAxes();
  m_view->getChart()->axisY()->setMin(0);
  m_view->getChart()->setAxisX(m_axis, m_series);
  m_view->getChart()->setAnimationOptions(QChart::AllAnimations);
}

void ChartPresenter::setModel(model::BenchmarkModel* model) {
  m_model = model;
  connectSignalsToSlots();
}

void ChartPresenter::connectSignalsToSlots() {
  connect(m_model, &model::BenchmarkModel::measurementActive, this,
          &ChartPresenter::onAddMeasurement);
  connect(m_model, &model::BenchmarkModel::measurementInactive, this,
          &ChartPresenter::onRemoveMeasurement);
}

void ChartPresenter::onAddMeasurement(model::Measurement mmt) {
  QString name = mmt.getName();
  double cpuTime = mmt.getCpuTime();
  double realTime = mmt.getRealTime();
  QBarSet* set = new QBarSet(name);
  *set << cpuTime << realTime;
  m_barSet[mmt.getId()] = set;
  m_series->append(set);
  m_view->getChart()->axisY()->setMax(calculateMaxY() + 10);
}

void ChartPresenter::onRemoveMeasurement(model::Measurement mmt) {
  QBarSet* set = m_barSet[mmt.getId()];
  m_series->remove(set);
  m_barSet.remove(mmt.getId());
  m_view->getChart()->axisY()->setMax(calculateMaxY());
}

double ChartPresenter::calculateMaxY() {
  double maxY = 50;
  foreach (QBarSet* barSet, m_barSet.values()) {
    if (barSet->at(0) > maxY) {
      maxY = barSet->at(0);
    }
    if (barSet->at(1) > maxY) {
      maxY = barSet->at(1);
    }
  }
  return maxY;
}

}  // namespace presenter
