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

#include "benchmarkproxymodel.h"

Q_LOGGING_CATEGORY(proxyModel, "proxyModel")

BenchmarkProxyModel::BenchmarkProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent) {}

bool BenchmarkProxyModel::lessThan(const QModelIndex& left,
                                   const QModelIndex& right) const {
  QVariant leftData = sourceModel()->data(left);
  QVariant rightData = sourceModel()->data(right);

  auto col = left.column();

  if (col == 0) {
    return leftData.toBool();
  } else if (col == 1 || col == 6) {
    return QString::localeAwareCompare(leftData.toString(),
                                       rightData.toString()) < 0;
  } else if (col == 2 || col == 3 || col == 4) {
    return leftData.toDouble() < rightData.toDouble();
  }

  return QString::localeAwareCompare(leftData.toString(),
                                     rightData.toString()) < 0;
}

bool BenchmarkProxyModel::filterAcceptsRow(
    int sourceRow,
    const QModelIndex& sourceParent) const {
  qCDebug(proxyModel) << "Row filtered: true ";
  QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
  if (sourceModel()->data(index).toString().toLower().trimmed().contains(
          filterRegExp())) {
    qCDebug(proxyModel) << "Row filtered: true ";
    return true;
  } else {
    qCDebug(proxyModel) << "Row filtered: true ";
    return false;
  }
}
