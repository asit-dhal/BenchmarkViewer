/*=========================================================================

   Program: QCommander

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   QCommander is a free software; you can redistribute it and/or modify it.


   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/

#include "chartviewwidget.h"

#include <QBarSet>
#include <QHBoxLayout>

Q_LOGGING_CATEGORY(chartView, "chartView");

ChartViewWidget::ChartViewWidget(QWidget* parent)
    : QWidget(parent), m_chartView(new QChartView) {
  init();
  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addWidget(m_chartView);
  setLayout(mainLayout);
}

void ChartViewWidget::init() {
  m_chart = new QChart;
  m_series = new QBarSeries;
  m_chart->addSeries(m_series);
  m_chart->legend()->setVisible(true);
  m_chart->legend()->setAlignment(Qt::AlignRight);
  QStringList categories;
  categories << "CPU Time"
             << "Real Time";
  m_axis = new QBarCategoryAxis();
  m_axis->append(categories);
  m_chart->createDefaultAxes();
  m_chart->axisY()->setMin(0);
  m_chart->setAxisX(m_axis, m_series);
  m_chart->setAnimationOptions(QChart::AllAnimations);
  m_chartView->setChart(m_chart);
  m_chartView->setRenderHint(QPainter::Antialiasing);
}

void ChartViewWidget::onAddMeasurement(Measurement mmt) {
  qCDebug(chartView) << "New Measurement: " << mmt;
  QString name = mmt.getName();
  double cpuTime = mmt.getCpuTime();
  double realTime = mmt.getRealTime();
  QBarSet* set = new QBarSet(name);
  *set << cpuTime << realTime;
  m_barSet[mmt.getId()] = set;
  m_series->append(set);
  m_chart->axisY()->setMax(calculateMaxY() + 10);
}

double ChartViewWidget::calculateMaxY() {
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

void ChartViewWidget::onRemoveMeasurement(Measurement mmt) {
  qCDebug(chartView) << "Removed Measurement: " << mmt;
  QBarSet* set = m_barSet[mmt.getId()];
  m_series->remove(set);
  m_barSet.remove(mmt.getId());
  m_chart->axisY()->setMax(calculateMaxY());
}
