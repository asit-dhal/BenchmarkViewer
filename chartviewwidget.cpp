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

#include <QHBoxLayout>

ChartViewWidget::ChartViewWidget(BenchmarkModel* model, QWidget* parent)
    : QWidget(parent),
      m_model(model),
      m_chart(new QChart),
      m_modelMapper(new QVXYModelMapper),
      m_chartView(new QChartView),
      m_series(new QLineSeries) {
  m_chart->setAnimationOptions(QChart::AllAnimations);
  m_series->setName("Bar 1");
  m_modelMapper->setXColumn(1);
  m_modelMapper->setYColumn(4);
  m_modelMapper->setSeries(m_series);
  m_modelMapper->setModel(m_model);
  m_chart->addSeries(m_series);
  m_chartView->setRenderHint(QPainter::Antialiasing);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addWidget(m_chartView);
  setLayout(mainLayout);
}

void ChartViewWidget::refresh(int colX, int colY) {
  m_modelMapper->setXColumn(colX);
  m_modelMapper->setYColumn(colY);
  m_modelMapper->setSeries(m_series);
  m_modelMapper->setModel(m_model);
  m_chart->addSeries(m_series);
}
