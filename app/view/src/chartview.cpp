/*=========================================================================

   Program: BenchmarkViewer

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   BenchmarkViewer is a free software; you can redistribute it and/or modify it.


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

#include "view/chartview.h"
#include <QBarSet>
#include <QHBoxLayout>
#include "model/measurement.h"
#include "view/globals.h"

Q_LOGGING_CATEGORY(chartView, "chartView");

namespace view {

ChartView::ChartView(QWidget* parent)
    : QWidget(parent), m_chartView(new QChartView) {
  m_chart = new QChart;
  m_chart->setAnimationOptions(QChart::AllAnimations);
  m_chartView->setChart(m_chart);
  m_chartView->setRenderHint(QPainter::Antialiasing);

  m_presenter = new presenter::ChartPresenter(this);

  // m_presenter->onAddMeasurementAttr(model::Measurement::Attributes::eCpuTime);
  // m_presenter->onAddMeasurementAttr(model::Measurement::Attributes::eRealTime);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addWidget(m_chartView);
  setLayout(mainLayout);
}

QChart* ChartView::getChart() const {
  return m_chart;
}

void ChartView::setModel(model::BenchmarkModel* model) {
  m_presenter->setModel(model);
  m_presenter->init();
}

}  // namespace view
