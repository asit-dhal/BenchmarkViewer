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

#ifndef YAXISSELECTORVIEW_H
#define YAXISSELECTORVIEW_H

#include <QStringList>
#include <QTableView>
class YAxisSelectorView : public QTableView {
  Q_OBJECT
 public:
  YAxisSelectorView(QWidget* parent = 0);
  ~YAxisSelectorView() = default;

 signals:
  void select();
  void selectAllRows();
  void clearSelection();
  void clearAllRows();

 private slots:
  void onContextMenuOnHeader(QPoint p);
  void onContextMenuOnBody(QPoint p);

 private:
  QHeaderView* m_header;

  QAction* m_select;
  QAction* m_selectAll;
  QAction* m_clearSelection;
  QAction* m_clearAllRows;
};

#endif  // YAXISSELECTORVIEW_H
