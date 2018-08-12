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

#include "view/benchmarkview.h"
#include <QHeaderView>
#include <QMenu>
#include "presenter/benchmarkpresenter.h"
#include "view/globals.h"

namespace view {

BenchmarkView::BenchmarkView(QWidget* parent) : QTableView(parent) {
  m_header = horizontalHeader();
  m_header->setSectionsMovable(true);
  m_header->setContextMenuPolicy(Qt::CustomContextMenu);
  this->setContextMenuPolicy(Qt::CustomContextMenu);

  m_moveLastAction = new QAction("MoveLast", this);
  m_moveFirstAction = new QAction("MoveFirst", this);
  m_select = new QAction(tr("Select"), this);
  m_selectAll = new QAction(tr("Select All"), this);
  m_clearSelection = new QAction(tr("Clear Selection"), this);
  m_clearAllRows = new QAction(tr("Clear All rows"), this);

  m_presenter = new presenter::BenchmarkPresenter(this);
}

void BenchmarkView::init() {
  qCDebug(VIEW_TAG) << "Initialization Finished";
  m_presenter->init();
}

void BenchmarkView::setModel(QAbstractItemModel* model) {
  QTableView::setModel(model);
  m_presenter->setModel(model);
}

QList<QAction*> BenchmarkView::getColumnShowHideActions() const {
  return m_columnShowHideActions;
}

QAction* BenchmarkView::getClearAllRows() {
  return m_clearAllRows;
}

QAction* BenchmarkView::getClearSelection() {
  return m_clearSelection;
}

QAction* BenchmarkView::getSelectAll() {
  return m_selectAll;
}

QAction* BenchmarkView::getSelect() {
  return m_select;
}

QAction* BenchmarkView::getMoveFirstAction() {
  return m_moveFirstAction;
}

QAction* BenchmarkView::getMoveLastAction() {
  return m_moveLastAction;
}

QHeaderView* BenchmarkView::getHeader() {
  return m_header;
}

}  // namespace view
