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

#include "benchmarkview.h"
#include <QHeaderView>
#include <QMenu>
#include "globals.h"

BenchmarkView::BenchmarkView(BmColumns* bmColumns, QWidget* parent)
    : QTableView(parent), m_bmColumns(bmColumns) {
  m_header = horizontalHeader();
  m_header->setSectionsMovable(true);
  m_header->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(m_header, SIGNAL(customContextMenuRequested(const QPoint&)), this,
          SLOT(onShowHeaderMenu(const QPoint&)));

  for (auto i = 0; i < m_bmColumns->getColumnCount(); i++) {
    auto col = m_bmColumns->indexToColumns(i);
    QAction* showHideColumn =
        new QAction(m_bmColumns->columnNameToString(col), this);
    showHideColumn->setCheckable(true);
    showHideColumn->setChecked(!m_bmColumns->isColumnHidden(col));
    connect(showHideColumn, &QAction::triggered, this, [=]() {
      if (m_bmColumns->isColumnHidden(col)) {
        emit m_bmColumns->showColumn(col);
      } else {
        emit m_bmColumns->hideColumn(col);
      }
    });
    m_columnShowHideActions.append(showHideColumn);
  }

  m_moveLastAction = new QAction("MoveLast", this);
  connect(m_moveLastAction, SIGNAL(triggered(bool)), this,
          SLOT(onSlotMoveLast()));
  m_moveFirstAction = new QAction("MoveFirst", this);
  connect(m_moveFirstAction, SIGNAL(triggered(bool)), this,
          SLOT(onSlotMoveFirst()));

  qCDebug(gui)
      << "signal[BmColumns::hideColumn] -> slot[BenchmarkView::onHideColumn]";
  connect(m_bmColumns, &BmColumns::hideColumn, this,
          &BenchmarkView::onHideColumn);
  qCDebug(gui)
      << "signal[BmColumns::showColumn] -> slot[BenchmarkView::onShowColumn]";
  connect(m_bmColumns, &BmColumns::showColumn, this,
          &BenchmarkView::onShowColumn);
}

void BenchmarkView::onShowHeaderMenu(QPoint p) {
  qCDebug(gui) << "context menu requested";
  QMenu menu;
  QPoint p2 = mapToGlobal(p);
  int logicIndex = m_header->logicalIndexAt(p);
  menu.addActions(m_columnShowHideActions);
  menu.addAction(m_moveLastAction);
  m_moveLastAction->setData(logicIndex);
  menu.addAction(m_moveFirstAction);
  m_moveFirstAction->setData(logicIndex);
  menu.exec(p2);
}

void BenchmarkView::onSlotMoveLast() {
  int last = m_header->count() - 1;
  int current = m_moveLastAction->data().toInt();
  int from = m_header->visualIndex(current);
  m_header->moveSection(from, last);
}

void BenchmarkView::onSlotMoveFirst() {
  int current = m_moveFirstAction->data().toInt();
  int from = m_header->visualIndex(current);
  m_header->moveSection(from, 0);
}

void BenchmarkView::onShowColumn(BmColumns::Columns col) {
  qCDebug(gui) << "Col: " << m_bmColumns->columnNameToString(col);
  showColumn(m_bmColumns->columnNameToIndex(col));
  updateColumnViewStatus();
}

void BenchmarkView::onHideColumn(BmColumns::Columns col) {
  qCDebug(gui) << "Col: " << m_bmColumns->columnNameToString(col);
  hideColumn(m_bmColumns->columnNameToIndex(col));
  updateColumnViewStatus();
}

void BenchmarkView::updateColumnViewStatus() {
  for (auto i = 0; i < m_bmColumns->getColumnCount(); i++) {
    auto col = m_bmColumns->indexToColumns(i);
    m_columnShowHideActions.at(i)->setChecked(
        !m_bmColumns->isColumnHidden(col));
  }
}
