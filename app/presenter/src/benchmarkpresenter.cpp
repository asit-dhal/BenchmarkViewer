#include "presenter/benchmarkpresenter.h"
#include <QAction>
#include <QHeaderView>
#include <QMenu>
#include "presenter/benchmarkdelegate.h"
#include "presenter/benchmarkproxymodel.h"
#include "presenter/presenter_globals.h"
#include "view/benchmarkview.h"

namespace presenter {

BenchmarkPresenter::BenchmarkPresenter(view::BenchmarkView* view,
                                       QObject* parent)
    : QObject(parent), m_view(view) {
  m_delegate = new BenchmarkDelegate(parent);
  m_view->setItemDelegate(m_delegate);
}

void BenchmarkPresenter::init() {
  if (m_view) {
    connectSignalsToSlots();
  }
  m_view->setEditTriggers(QAbstractItemView::CurrentChanged);
  m_view->setSortingEnabled(true);
  m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_view->sortByColumn(1, Qt::DescendingOrder);
  qCDebug(PRESENTER_TAG) << "Initialization Finished";
}

bool BenchmarkPresenter::setModel(QAbstractItemModel* model) {
  m_model = model;
  m_proxyModel = new BenchmarkProxyModel(m_model);
  m_proxyModel->setSourceModel(m_model);
  m_view->setModel(m_proxyModel);
  return true;
}

void BenchmarkPresenter::onContextMenuOnHeader(QPoint p) {
  QMenu menu;
  QPoint p2 = m_view->mapToGlobal(p);
  int logicIndex = m_view->getHeader()->logicalIndexAt(p);
  menu.addActions(m_view->getColumnShowHideActions());
  menu.addSeparator();
  menu.addAction(m_view->getMoveLastAction());
  m_view->getMoveLastAction()->setData(logicIndex);
  menu.addAction(m_view->getMoveFirstAction());
  m_view->getMoveFirstAction()->setData(logicIndex);
  menu.exec(p2);
}

void BenchmarkPresenter::onContextMenuOnBody(QPoint p) {
  QMenu menu;
  QPoint p2 = m_view->mapToGlobal(p);
  menu.addAction(m_view->getSelect());
  menu.addAction(m_view->getSelectAll());
  menu.addAction(m_view->getClearSelection());
  menu.addAction(m_view->getClearAllRows());
  menu.exec(p2);
}

void BenchmarkPresenter::onSlotMoveLast() {
  int last = m_view->getHeader()->count() - 1;
  int current = m_view->getMoveLastAction()->data().toInt();
  int from = m_view->getHeader()->visualIndex(current);
  m_view->getHeader()->moveSection(from, last);
}

void BenchmarkPresenter::onSlotMoveFirst() {
  int current = m_view->getMoveFirstAction()->data().toInt();
  int from = m_view->getHeader()->visualIndex(current);
  m_view->getHeader()->moveSection(from, 0);
}

void BenchmarkPresenter::onShowColumn(int colIdx) {
  m_view->showColumn(colIdx);
}

void BenchmarkPresenter::onHideColumn(int colIdx) {
  m_view->hideColumn(colIdx);
}

void BenchmarkPresenter::connectSignalsToSlots() {
  connect(m_view->getHeader(), &QHeaderView::customContextMenuRequested, this,
          &BenchmarkPresenter::onContextMenuOnHeader);
  connect(m_view, &view::BenchmarkView::customContextMenuRequested, this,
          &BenchmarkPresenter::onContextMenuOnBody);
  connect(m_view->getMoveLastAction(), &QAction::triggered, this,
          &BenchmarkPresenter::onSlotMoveLast);
  connect(m_view->getMoveFirstAction(), &QAction::triggered, this,
          &BenchmarkPresenter::onSlotMoveFirst);

  connect(m_view->getSelect(), &QAction::triggered,
          [&]() { emit m_view->select(); });

  connect(m_view->getSelectAll(), &QAction::triggered,
          [&]() { emit m_view->selectAllRows(); });

  connect(m_view->getClearSelection(), &QAction::triggered,
          [&]() { emit m_view->clearSelection(); });

  connect(m_view->getClearAllRows(), &QAction::triggered,
          [&]() { emit m_view->clearAllRows(); });
}

}  // namespace presenter
