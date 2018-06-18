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

#include "yaxisselectorview.h"
#include <QHeaderView>
#include <QMenu>
#include "viewglobals.h"

YAxisSelectorView::YAxisSelectorView(QWidget* parent) : QTableView(parent) {
  m_header = horizontalHeader();
  m_header->setSectionsMovable(true);
  m_header->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(m_header, SIGNAL(customContextMenuRequested(const QPoint&)), this,
          SLOT(onContextMenuOnHeader(const QPoint&)));

  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this,
          SLOT(onContextMenuOnBody(const QPoint&)));

  m_select = new QAction(tr("Select"), this);
  connect(m_select, &QAction::triggered, [&]() { emit this->select(); });
  m_selectAll = new QAction(tr("Select All"), this);
  connect(m_selectAll, &QAction::triggered,
          [&]() { emit this->selectAllRows(); });
  m_clearSelection = new QAction(tr("Clear Selection"), this);
  connect(m_clearSelection, &QAction::triggered,
          [&]() { emit this->clearSelection(); });
  m_clearAllRows = new QAction(tr("Clear All rows"), this);
  connect(m_clearAllRows, &QAction::triggered,
          [&]() { emit this->clearAllRows(); });
}

void YAxisSelectorView::onContextMenuOnBody(QPoint p) {
  qCDebug(view) << "context menu requested";
  QMenu menu;
  QPoint p2 = mapToGlobal(p);
  menu.addAction(m_select);
  menu.addAction(m_selectAll);
  menu.addAction(m_clearSelection);
  menu.addAction(m_clearAllRows);
  menu.exec(p2);
}
