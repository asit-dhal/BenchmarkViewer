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
#include "benchmarkmodel.h"

Q_LOGGING_CATEGORY(proxyModel, "proxyModel")

BenchmarkProxyModel::BenchmarkProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent), m_onlySelected(false) {}

bool BenchmarkProxyModel::lessThan(const QModelIndex& left,
                                   const QModelIndex& right) const {
  QVariant leftData = sourceModel()->data(left);
  QVariant rightData = sourceModel()->data(right);

  auto col = static_cast<Columns>(left.column());

  switch (col) {
    case Columns::STATUS:
      return leftData.toBool();
    case Columns::ITERATIONS:
    case Columns::REAL_TIME:
    case Columns::CPU_TIME:
      return leftData.toDouble() < rightData.toDouble();
    case Columns::NAME:
    case Columns::FILENAME:
    default:
      return QString::localeAwareCompare(leftData.toString(),
                                         rightData.toString()) < 0;
  }
}

bool BenchmarkProxyModel::filterAcceptsRow(
    int sourceRow,
    const QModelIndex& sourceParent) const {
  QModelIndex statusIndex = sourceModel()->index(
      sourceRow, static_cast<int>(Columns::STATUS), sourceParent);
  QModelIndex nameIndex = sourceModel()->index(
      sourceRow, static_cast<int>(Columns::FILENAME), sourceParent);

  if (m_onlySelected) {
    if (!sourceModel()->data(statusIndex).toBool()) {
      return false;
    }
  }

  if (sourceModel()->data(nameIndex).toString().toLower().trimmed().contains(
          filterRegExp())) {
    return true;
  } else {
    return false;
  }
}

bool BenchmarkProxyModel::onlySelected() const {
  return m_onlySelected;
}

void BenchmarkProxyModel::setOnlySelected(bool onlySelected) {
  m_onlySelected = onlySelected;
  invalidateFilter();
}
