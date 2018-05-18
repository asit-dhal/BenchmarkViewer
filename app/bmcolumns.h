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

#ifndef BMCOLUMNS_H
#define BMCOLUMNS_H

#include <QMap>
#include <QMetaType>
#include <QObject>

class BmColumns : public QObject {
  Q_OBJECT
 public:
  enum class Columns {
    INVALID,
    STATUS,
    NAME,
    ITERATIONS,
    REAL_TIME,
    CPU_TIME,
    TIME_UNIT,
    BYTES_PER_SECOND,
    ITEMS_PER_SECOND,
    LABEL,
    IS_ERROR_OCCURED,
    ERROR_MESSAGE,
    FILENAME
  };

  enum class ColumnPlotAttr {
    INVALID,
    NONE,
    X_AXIS,
    Y_AXIS,
  };

  int getColumnCount() { return m_columnIndex.size(); }

  QString columnNameToString(Columns cols);
  int columnNameToIndex(Columns cols);
  BmColumns::Columns indexToColumns(int index);
  bool isColumnHidden(Columns cols);
  BmColumns(QObject* parent = nullptr);

  QMap<Columns, ColumnPlotAttr>& getColPlotAttrs();

 signals:
  void hideColumn(Columns);
  void showColumn(Columns);
  void plotAttrUpdated(Columns, ColumnPlotAttr);

 public slots:
  void onHideColumn(Columns col);
  void onShowColumn(Columns col);

 private:
  QMap<Columns, bool> m_columnViewStatus;
  QMap<Columns, int> m_columnIndex;
  QMap<Columns, QString> m_columnName;
  QMap<Columns, ColumnPlotAttr> m_colPlotAttrs;
};

Q_DECLARE_METATYPE(BmColumns::Columns);
Q_DECLARE_METATYPE(BmColumns::ColumnPlotAttr);

QDebug operator<<(QDebug d, const BmColumns::Columns& mmt);
QDebug operator<<(QDebug d, const BmColumns::ColumnPlotAttr& attr);

#endif  // BMCOLUMNS_H
