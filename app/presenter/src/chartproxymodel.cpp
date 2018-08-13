#include "presenter/chartproxymodel.h"

namespace presenter {

ChartProxyModel::ChartProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent) {}

bool ChartProxyModel::filterAcceptsRow(int sourceRow,
                                       const QModelIndex& sourceParent) const {
  QModelIndex nameIndex = sourceModel()->index(sourceRow, 0, sourceParent);
  if (sourceModel()->data(nameIndex).toBool())
    return true;
  else
    return false;
}

bool ChartProxyModel::filterAcceptsColumn(
    int sourceColumn,
    const QModelIndex& sourceParent) const {
  Q_UNUSED(sourceParent)
  if (sourceColumn == 2 || sourceColumn == 3)
    return false;

  return true;
}

}  // namespace presenter
