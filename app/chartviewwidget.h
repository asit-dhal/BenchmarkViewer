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

#include <QBarCategoryAxis>
#include <QBarSet>
#include <QLoggingCategory>
#include <QMap>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QVXYModelMapper>
#include <QtWidgets>
#include "measurement.h"

Q_DECLARE_LOGGING_CATEGORY(chartView);

QT_CHARTS_USE_NAMESPACE

class ChartViewWidget : public QWidget {
 public:
  ChartViewWidget(QWidget* parent = nullptr);

 public slots:
  void onAddMeasurement(Measurement mmt);
  void onRemoveMeasurement(Measurement mmt);

 private:
  void init();
  double calculateMaxY();

  double m_maxY = 0;
  QBarCategoryAxis* m_axis;
  QChart* m_chart;
  QChartView* m_chartView;
  QBarSeries* m_series;
  QMap<int, QBarSet*> m_barSet;
};

#endif  // CHARTVIEWWIDGET_H
