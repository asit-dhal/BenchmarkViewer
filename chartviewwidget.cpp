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

ChartViewWidget::ChartViewWidget(BenchmarkProxyModel* model, QWidget* parent)
    : QWidget(parent), m_model(model), m_chartView(new QChartView) {
  m_chartView->setRenderHint(QPainter::Antialiasing);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addWidget(m_chartView);
  setLayout(mainLayout);
}

void ChartViewWidget::update() {
  m_chart = new QChart;
  m_series = new QBarSeries;
  auto entryCount = m_model->rowCount();
  qCDebug(chartView) << "Entry count: " << entryCount;
  for (auto i = 0; i < entryCount; i++) {
    QModelIndex nameIndex = m_model->index(i, 1, QModelIndex());
    QModelIndex valueIndex = m_model->index(i, 4, QModelIndex());
    QString name = m_model->data(nameIndex).toString();
    double val = m_model->data(valueIndex).toDouble();
    QBarSet* set = new QBarSet(name);
    qCDebug(chartView) << "Entry [" << i << "]: " << name << " -> " << val;
    *set << val;
    m_series->append(set);
  }
  m_chart->addSeries(m_series);
  m_chart->legend()->setVisible(true);
  m_chart->legend()->setAlignment(Qt::AlignRight);
  m_chart->createDefaultAxes();
  m_chart->setAnimationOptions(QChart::AllAnimations);
  m_chartView->setChart(m_chart);
  m_chartView->setRenderHint(QPainter::Antialiasing);
}
