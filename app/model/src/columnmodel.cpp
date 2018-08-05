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

#include "model/columnmodel.h"

namespace model {

ColumnModel::ColumnModel(QObject* parent) : QAbstractListModel(parent) {}

int ColumnModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return m_columns.size();
}

QVariant ColumnModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  if (index.row() >= m_columns.size() || index.row() < 0) {
    return QVariant();
  }

  if (role == Qt::DisplayRole) {
    return Measurement::getAttributeNames()[m_columns.at(index.row())];
  } else if (role == AttrRole) {
    return QVariant::fromValue(m_columns.at(index.row()));
  }
  return QVariant();
}

void ColumnModel::addColumn(Measurement::Attributes attr) {
  beginResetModel();
  m_columns.append(attr);
  endResetModel();
}

void ColumnModel::removeColumn(Measurement::Attributes attr) {
  beginResetModel();
  m_columns.removeOne(attr);
  endResetModel();
}

}  // namespace model
