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

Q_LOGGING_CATEGORY(benchmarkView, "benchmarkView")

BenchmarkView::BenchmarkView(QWidget* parent) : QTableView(parent) {
  m_header = horizontalHeader();
  m_header->setSectionsMovable(true);
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this,
          SLOT(onShowHeaderMenu(const QPoint&)));

  m_hideAction = new QAction("Hide", this);
  connect(m_hideAction, SIGNAL(triggered(bool)), this,
          SLOT(onSlotHideColumn()));

  m_moveLastAction = new QAction("MoveLast", this);
  connect(m_moveLastAction, SIGNAL(triggered(bool)), this,
          SLOT(onSlotMoveLast()));
  m_moveFirstAction = new QAction("MoveFirst", this);
  connect(m_moveFirstAction, SIGNAL(triggered(bool)), this,
          SLOT(onSlotMoveFirst()));
}

void BenchmarkView::onShowHeaderMenu(QPoint p) {
  qCDebug(benchmarkView) << "context menu requested";
  QMenu menu;
  QPoint p2 = mapToGlobal(p);

  int logicIndex = m_header->logicalIndexAt(p);
  m_hideAction->setData(logicIndex);

  if (model()->columnCount() - m_currentHiddenColumns.size() > 1) {
    QString nameCurrent =
        model()->headerData(logicIndex, Qt::Horizontal).toString();
    m_hideAction->setText("Hide " + nameCurrent);
    menu.addAction(m_hideAction);
  }

  menu.addAction(m_moveLastAction);
  m_moveLastAction->setData(logicIndex);
  menu.addAction(m_moveFirstAction);
  m_moveFirstAction->setData(logicIndex);

  for (int num : m_currentHiddenColumns) {
    QString name = model()->headerData(num, Qt::Horizontal).toString();
    menu.addAction("Show " + name, this, SLOT(onShowHiddenColumn()));
    menu.actions().last()->setData(num);
  }
  menu.exec(p2);
}

void BenchmarkView::onSlotHideColumn() {
  int colNum = m_hideAction->data().toInt();
  m_currentHiddenColumns.append(colNum);
  qCDebug(benchmarkView) << "Hiding Column: " << colNum;
  hideColumn(colNum);
}

void BenchmarkView::onShowHiddenColumn() {
  QAction* act = (QAction*)sender();
  int ind = act->data().toInt();
  qCDebug(benchmarkView) << "Showing Column: " << ind;
  showColumn(ind);
  m_currentHiddenColumns.removeOne(ind);
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
