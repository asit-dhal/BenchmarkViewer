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

#include "plotconfig.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include "bmcolumns.h"
#include "globals.h"
#include "xaxiscombobox.h"

PlotConfig::PlotConfig(BmColumns* bmColumns, QWidget* parent)
    : QWidget(parent), m_bmColumns(bmColumns) {
  QLabel* xAxisLabel = new QLabel(tr("X-Axis"));
  m_xAxisSelector = new XAxisComboBox(bmColumns, this);
  m_yAxisSelector = new QTableWidget;

  m_yAxisSelector->setColumnCount(2);
  QStringList horizontalHeaders;
  horizontalHeaders << "Attributes"
                    << "Status";
  m_yAxisSelector->setHorizontalHeaderLabels(horizontalHeaders);
  m_yAxisSelector->setShowGrid(true);
  m_yAxisSelector->setSelectionMode(QAbstractItemView::SingleSelection);
  m_yAxisSelector->setSelectionBehavior(QAbstractItemView::SelectRows);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(xAxisLabel);
  layout->addWidget(m_xAxisSelector);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(layout);
  mainLayout->addWidget(m_yAxisSelector);

  setLayout(mainLayout);

  connect(m_xAxisSelector, &XAxisComboBox::currentColumnChanged, this,
          &PlotConfig::xAxisAttrChanged);
  connect(m_yAxisSelector, &QTableWidget::cellChanged, this,
          &PlotConfig::yAxisAttrChanged);

  update();
}

void PlotConfig::update() {
  auto& colAttrs = m_bmColumns->getColPlotAttrs();
  int row = 0;
  m_xAxisSelector->update(m_bmColumns);
  for (auto key : colAttrs.keys()) {
    // sex y-axis
    if (colAttrs[key] == BmColumns::ColumnPlotAttr::Y_AXIS ||
        colAttrs[key] == BmColumns::ColumnPlotAttr::NONE) {
      m_yAxisSelector->insertRow(row);
      m_yAxisSelector->setItem(
          row, 0, new QTableWidgetItem(m_bmColumns->columnNameToString(key)));
      QTableWidgetItem* item = new QTableWidgetItem();
      item->data(Qt::CheckStateRole);
      if (colAttrs[key] == BmColumns::ColumnPlotAttr::Y_AXIS) {
        item->setCheckState(Qt::Checked);
      } else {
        item->setCheckState(Qt::Unchecked);
      }
      m_yAxisSelector->setItem(row, 1, item);
      row++;
    }
  }

  m_yAxisSelector->resizeColumnsToContents();
}

void PlotConfig::xAxisAttrChanged(BmColumns::Columns cols) {
  qCDebug(gui) << "column: " << cols;
}

void PlotConfig::yAxisAttrChanged(int row, int col) {
  if (m_yAxisSelector->item(row, col)->checkState() ==
      Qt::CheckState::Checked) {
    // emit m_bmColumns->plotAttrUpdated(Columns, ColumnPlotAttr);
  }
}
