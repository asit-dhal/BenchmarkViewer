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

#ifndef BENCHMARKVIEW_H
#define BENCHMARKVIEW_H

#include <QTableView>

class QHeaderView;

namespace presenter {
class BenchmarkPresenter;
}

namespace view {

// View should do the following
// - create visual components in the constructor
// - create presenters in the constructor
// - initialize
// - set model
class BenchmarkView : public QTableView {
  Q_OBJECT

 public:
  BenchmarkView(QWidget* parent = 0);
  ~BenchmarkView() = default;
  void init();
  void setBenchmarkModel(QAbstractItemModel* model);
  presenter::BenchmarkPresenter* getPresenter();

  QHeaderView* getHeader();

  QAction* getMoveLastAction();
  QAction* getMoveFirstAction();
  QAction* getSelect();
  QAction* getSelectAll();
  QAction* getClearSelection();
  QAction* getClearAllRows();
  QList<QAction*> getColumnShowHideActions() const;

 signals:
  void select();
  void selectAllRows();
  void clearSelection();
  void clearAllRows();

 private:
  QStringList m_columns;
  QHeaderView* m_header;
  QList<QAction*> m_columnShowHideActions;

  QAction* m_moveLastAction;
  QAction* m_moveFirstAction;
  QAction* m_select;
  QAction* m_selectAll;
  QAction* m_clearSelection;
  QAction* m_clearAllRows;

  QList<int> m_currentHiddenColumns;
  presenter::BenchmarkPresenter* m_presenter;
};

}  // namespace view
#endif  // BENCHMARKVIEW_H
