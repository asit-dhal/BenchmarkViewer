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
#include "benchmarkmodel.h"

Q_LOGGING_CATEGORY(proxyModel, "proxyModel")

BenchmarkProxyModel *BenchmarkProxyModel::m_pInstance = nullptr;

BenchmarkProxyModel *BenchmarkProxyModel::getInstance()
{
    return m_pInstance;
}

BenchmarkProxyModel::BenchmarkProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    m_pInstance = this;
}

bool BenchmarkProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
	QVariant leftData = sourceModel()->data(left);
	QVariant rightData = sourceModel()->data(right);

	using Columns = BenchmarkModel::Columns;
    switch (static_cast<Columns>(left.column())) {
	case Columns::eStatus:
		return leftData.toBool();
    case Columns::eIterations:
    case Columns::eRealTime:
    case Columns::eCpuTime:
		return leftData.toDouble() < rightData.toDouble();
    case Columns::eName:
    case Columns::eFilename:
    default:
        return QString::localeAwareCompare(leftData.toString(), rightData.toString()) < 0;
	}
}

bool BenchmarkProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex nameIndex = sourceModel()->index(sourceRow,
        static_cast<int>(BenchmarkModel::Columns::eName), sourceParent);

    if (sourceModel()->data(nameIndex).toString().toLower().trimmed()
            .contains(filterRegExp())) {
		return true;
    } else {
		return false;
	}
}
