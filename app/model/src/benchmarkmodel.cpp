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

#include "model/benchmarkmodel.h"
#include <QAbstractItemModel>
#include <QColor>
#include <QFileInfo>
#include "model/measurement.h"
#include "model/model_globals.h"

namespace model {

BenchmarkModel::BenchmarkModel(ColumnModel* columnModel, QObject* parent)
    : QAbstractTableModel(parent), m_columnModel(columnModel) {
  if (!m_columnModel) {
    qCWarning(MODEL_TAG) << "columnModel is null";
  }
}

void BenchmarkModel::setColumnModel(ColumnModel* columnModel) {
  if (m_columnModel) {
    qCWarning(MODEL_TAG) << "columnModel will be reset";
  }
  m_columnModel = columnModel;
}

void BenchmarkModel::addMeasurements(Measurements mmts) {
  beginResetModel();
  m_mmts.append(mmts);
  qCWarning(MODEL_TAG) << mmts.size() << "measurements added";
  endResetModel();
}

void BenchmarkModel::addMeasurement(Measurement mmt) {
  beginResetModel();
  m_mmts.append(mmt);
  qCWarning(MODEL_TAG) << "one measurement added";
  endResetModel();
}

void BenchmarkModel::removeMeasurement(int id) {
  beginResetModel();
  for (auto itr = m_mmts.begin(); itr != m_mmts.end(); itr++) {
    if (itr->getId() == id) {
      itr = m_mmts.erase(itr);
    } else {
      ++itr;
    }
  }
  endResetModel();
}

QVariant BenchmarkModel::headerData(int section,
                                    Qt::Orientation orientation,
                                    int role) const {
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Horizontal) {
    if (!m_columnModel) {
      qCWarning(MODEL_TAG) << "columnModel is null";
      return QVariant();
    }
    if (section >= m_columnModel->rowCount())
      return QVariant();
    return m_columnModel->data(createIndex(section, 0));
  } else if (orientation == Qt::Vertical) {
    return QString("%1").arg(section + 1);
  } else {
    return QVariant();
  }
}

int BenchmarkModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return m_mmts.size();
}

int BenchmarkModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  if (!m_columnModel) {
    qCWarning(MODEL_TAG) << "columnModel is null";
    return 0;
  }
  return m_columnModel->rowCount();
}

QVariant BenchmarkModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (index.row() >= m_mmts.size() || index.row() < 0)
    return QVariant();

  if (role == Qt::DisplayRole) {
    if (!m_columnModel) {
      qCWarning(MODEL_TAG) << "columnModel is null";
      return QVariant();
    }
    auto colAttr =
        m_columnModel
            ->data(createIndex(index.column(), 0), ColumnModel::AttrRole)
            .value<Measurement::Attributes>();
    switch (colAttr) {
      case Measurement::Attributes::eIsSelected:
        return m_mmts.at(index.row()).isSelected();
      case Measurement::Attributes::eName:
        return m_mmts.at(index.row()).getName();
      case Measurement::Attributes::eRealTime:
        return m_mmts.at(index.row()).getRealTime();
      case Measurement::Attributes::eCpuTime:
        return m_mmts.at(index.row()).getCpuTime();
      case Measurement::Attributes::eTimeUnit:
        return m_mmts.at(index.row()).getTimeUnit();
      default:
        return QVariant();
    }
  }

  if (role == Qt::BackgroundColorRole) {
    if (m_mmts.at(index.row()).isSelected()) {
      return QColor(Qt::lightGray);
    } else {
      return QColor(Qt::white);
    }
  }

  return QVariant();
}

Qt::ItemFlags BenchmarkModel::flags(const QModelIndex& index) const {
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractItemModel::flags(index);
}

bool BenchmarkModel::setData(const QModelIndex& index,
                             const QVariant& value,
                             int role) {
  if (index.isValid() && role == Qt::EditRole) {
    if (!m_columnModel) {
      qCWarning(MODEL_TAG) << "columnModel is null";
      return false;
    }
    auto row = index.row();
    auto colAttr =
        m_columnModel
            ->data(createIndex(index.column(), 0), ColumnModel::AttrRole)
            .value<Measurement::Attributes>();
    if (colAttr == Measurement::Attributes::eIsSelected &&
        m_mmts[row].isSelected() != value.toBool()) {
      m_mmts[row].setSelected(value.toBool());
      emit dataChanged(createIndex(index.row(), 0),
                       createIndex(index.row(), m_columnModel->rowCount() - 1));

      return true;
    }
  }
  return false;
}

}  // namespace model
