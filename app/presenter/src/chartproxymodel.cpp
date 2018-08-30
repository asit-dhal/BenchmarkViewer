#include "presenter/chartproxymodel.h"
#include "presenter/presenter_globals.h"

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
  qCDebug(PRESENTER_TAG) << "called";
  if (sourceColumn == 2 || sourceColumn == 3)
    return true;

  return false;
}

}  // namespace presenter
