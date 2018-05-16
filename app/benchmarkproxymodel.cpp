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

#include "benchmarkproxymodel.h"
#include "bmcolumns.h"

Q_LOGGING_CATEGORY(proxyModel, "proxyModel")

BenchmarkProxyModel::BenchmarkProxyModel(BmColumns* bmColumns, QObject* parent)
    : QSortFilterProxyModel(parent), m_bmColumns(bmColumns) {}

bool BenchmarkProxyModel::lessThan(const QModelIndex& left,
                                   const QModelIndex& right) const {
  QVariant leftData = sourceModel()->data(left);
  QVariant rightData = sourceModel()->data(right);

  switch (m_bmColumns->indexToColumns(left.column())) {
    case BmColumns::Columns::STATUS:
      return leftData.toBool();
    case BmColumns::Columns::ITERATIONS:
    case BmColumns::Columns::REAL_TIME:
    case BmColumns::Columns::CPU_TIME:
      return leftData.toDouble() < rightData.toDouble();
    case BmColumns::Columns::NAME:
    case BmColumns::Columns::FILENAME:
    default:
      return QString::localeAwareCompare(leftData.toString(),
                                         rightData.toString()) < 0;
  }
}

bool BenchmarkProxyModel::filterAcceptsRow(
    int sourceRow,
    const QModelIndex& sourceParent) const {
  QModelIndex nameIndex = sourceModel()->index(
      sourceRow, m_bmColumns->columnNameToIndex(BmColumns::Columns::FILENAME),
      sourceParent);

  if (sourceModel()->data(nameIndex).toString().toLower().trimmed().contains(
          filterRegExp())) {
    return true;
  } else {
    return false;
  }
}
