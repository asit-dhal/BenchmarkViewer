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

#ifndef CHARTVIEWWIDGET_H
#define CHARTVIEWWIDGET_H

#include "model/benchmarkmodel.h"
#include "presenter/chartpresenter.h"

#include <QBarCategoryAxis>
#include <QBarSet>
#include <QLoggingCategory>
#include <QMap>
#include <QVXYModelMapper>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QVXYModelMapper>
#include <QtWidgets>

Q_DECLARE_LOGGING_CATEGORY(chartView);

QT_CHARTS_USE_NAMESPACE

namespace view {

class ChartView : public QWidget {
 public:
  ChartView(QWidget* parent = nullptr);
  QChart* getChart() const;
  void setModel(model::BenchmarkModel* model);

 private:
  QChart* m_chart;
  QChartView* m_chartView;
  presenter::ChartPresenter* m_presenter;
};

}  // namespace view

#endif  // CHARTVIEWWIDGET_H
