#ifndef CHARTPROXYMODEL_H
#define CHARTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QString>

namespace presenter {

class ChartProxyModel : public QSortFilterProxyModel {
 public:
  ChartProxyModel(QObject* parent = nullptr);

 protected:
  bool filterAcceptsRow(int sourceRow,
                        const QModelIndex& sourceParent) const override;
  bool filterAcceptsColumn(int source_column,
                           const QModelIndex& source_parent) const override;
};

}  // namespace presenter

#endif
