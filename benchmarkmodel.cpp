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

#include "benchmarkmodel.h"
#include <QAbstractItemModel>

#include <QDebug>

BenchmarkModel::BenchmarkModel(QObject* parent) : QAbstractTableModel(parent) {}

void BenchmarkModel::addBenchmark(QString filename, Benchmark benchmark) {
  auto mmt = benchmark.getMeasurements();
  for (auto itr = mmt.begin(); itr != mmt.end(); itr++) {
    BenchmarkViewUnit unit;
    unit.filename = filename;
    unit.measurement = *itr;
    m_benchmarks.append(unit);
  }

  emit layoutChanged();
  emit dataChanged(createIndex(0, 0), createIndex(m_benchmarks.size(), 7));
}

void BenchmarkModel::removeBenchmark(QString filename) {
  QList<BenchmarkViewUnit>::iterator itr = m_benchmarks.begin();
  while (itr != m_benchmarks.end()) {
    if (filename.compare(itr->filename, Qt::CaseInsensitive)) {
      itr = m_benchmarks.erase(itr);
    } else {
      ++itr;
    }
  }

  emit layoutChanged();
  emit QAbstractItemModel::dataChanged(createIndex(0, 0),
                                       createIndex(m_benchmarks.size(), 7));
}

QVariant BenchmarkModel::headerData(int section,
                                    Qt::Orientation orientation,
                                    int role) const {
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return QString(tr("Status"));
      case 1:
        return QString(tr("Benchmark Name"));
      case 2:
        return QString(tr("Iterations"));
      case 3:
        return QString(tr("Realtime"));
      case 4:
        return QString(tr("Cpu Time"));
      case 5:
        return QString(tr("Timeunit"));
      case 6:
        return QString(tr("Filename"));
      default:
        return QVariant();
    }
  } else if (orientation == Qt::Vertical) {
    return QString("%1").arg(section + 1);
  } else {
    return QVariant();
  }
}

int BenchmarkModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return m_benchmarks.size();
}

int BenchmarkModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return 7;
}

QVariant BenchmarkModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (index.row() >= m_benchmarks.size() || index.row() < 0)
    return QVariant();

  if (role == Qt::DisplayRole) {
    BenchmarkViewUnit viewunit = m_benchmarks.at(index.row());
    switch (index.column()) {
      case 0:
        return "";
      case 1:
        return viewunit.measurement.getName();
      case 2:
        return viewunit.measurement.getIterations();
      case 3:
        return viewunit.measurement.getRealTime();
      case 4:
        return viewunit.measurement.getCpuTime();
      case 5:
        return viewunit.measurement.getTimeUnit();
      case 6:
        return viewunit.filename;
      default:
        return QVariant();
    }
  }

  return QVariant();
}
