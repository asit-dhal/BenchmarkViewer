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

#include "benchmarkmodel.h"
#include <QAbstractItemModel>
#include <QColor>
#include <QFileInfo>
#include "bmcolumns.h"

Q_LOGGING_CATEGORY(benchmarkModel, "benchmarkModel")

BenchmarkModel::BenchmarkModel(BmColumns* bmColumns, QObject* parent)
    : QAbstractTableModel(parent), m_bmColumns(bmColumns) {}

void BenchmarkModel::addBenchmark(QString filename, Benchmark benchmark)
{
	auto mmt = benchmark.getMeasurements();
	qCDebug(benchmarkModel) << "Adding benchmark file: " << filename;
	beginResetModel();
	for (auto itr = mmt.begin(); itr != mmt.end(); itr++)
	{
		BenchmarkViewUnit unit;
		unit.filename = filename;
		unit.measurement = *itr;
		m_benchmarks.append(unit);
	}
	
	endResetModel();
}

void BenchmarkModel::removeBenchmark(QString filename) 
{
	QList<BenchmarkViewUnit>::iterator itr = m_benchmarks.begin();
	qCDebug(benchmarkModel) << "Removing benchmark file: " << filename;

	beginResetModel();
	while (itr != m_benchmarks.end()) 
	{
		if (filename.compare(itr->filename, Qt::CaseInsensitive) == 0) 
		{
			if (itr->isSelected) 
			{
				emit measurementInactive(itr->measurement);
			}
			itr = m_benchmarks.erase(itr);
		}
		else
		{
			++itr;
		}
	}
	endResetModel();

	qCDebug(benchmarkModel) << "All benchmarks removed from the file: "
                          << filename;
}

void BenchmarkModel::setMeasurementColor(int id, QString color)
{
	qCDebug(benchmarkModel) << "Setting Measurement id=" << id << " color=" << color;
	for (auto rowIndex = 0; rowIndex < rowCount(); rowIndex++)
	{
		if (m_benchmarks[rowIndex].measurement.getId() == id)
		{
			setData(createIndex(rowIndex, columnCount()), QVariant::fromValue(color), Qt::BackgroundColorRole);
			break;
		}
	}
}

QVariant BenchmarkModel::headerData(int section,
                                    Qt::Orientation orientation,
                                    int role) const
{
	if (role != Qt::DisplayRole) 
	{
		return QVariant();
	}

	if (orientation == Qt::Horizontal) 
	{
		BmColumns::Columns cols = m_bmColumns->indexToColumns(section);
		if (cols != BmColumns::Columns::INVALID) 
		{
			return m_bmColumns->columnNameToString(cols);
		} 
		else 
		{
			return QVariant();
		}
	}
	else if (orientation == Qt::Vertical) 
	{
		return QString("%1").arg(section + 1);
	}
	else
	{
		return QVariant();
	}
}

int BenchmarkModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return m_benchmarks.size();
}

int BenchmarkModel::columnCount(const QModelIndex& parent) const 
{
	Q_UNUSED(parent);
	return m_bmColumns->getColumnCount();
}

QVariant BenchmarkModel::data(const QModelIndex& index, int role) const 
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= m_benchmarks.size() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		BenchmarkViewUnit viewunit = m_benchmarks.at(index.row());
		BmColumns::Columns cols = m_bmColumns->indexToColumns(index.column());
		switch (cols)
		{
		case BmColumns::Columns::STATUS:
			return viewunit.isSelected;
		case BmColumns::Columns::NAME:
			return viewunit.measurement.getName();
		case BmColumns::Columns::ITERATIONS:
			return viewunit.measurement.getIterations();
		case BmColumns::Columns::REAL_TIME:
			return viewunit.measurement.getRealTime();
		case BmColumns::Columns::CPU_TIME:
			return viewunit.measurement.getCpuTime();
		case BmColumns::Columns::TIME_UNIT:
			return viewunit.measurement.getTimeUnit();
		case BmColumns::Columns::FILENAME:
			return QFileInfo(viewunit.filename).fileName();
		default:
			return QVariant();
		}
	}

	if (role == Qt::ToolTipRole)
	{
		BenchmarkViewUnit viewunit = m_benchmarks.at(index.row());
		BmColumns::Columns cols = m_bmColumns->indexToColumns(index.column());
		switch (cols)
		{
		case BmColumns::Columns::FILENAME:
			return viewunit.filename;
		default:
			return QVariant();
		}
	}

	if (role == Qt::BackgroundColorRole) 
	{
		BenchmarkViewUnit viewunit = m_benchmarks.at(index.row());
		if (viewunit.isSelected)
		{
			if (viewunit.hexColor == "#000000")
			{
				return QColor(Qt::lightGray);
			}
			else
			{
				return QColor(viewunit.hexColor);
			}
			
		}
		else 
		{
			return QColor(Qt::white);
		}
	}

	return QVariant();
}

Qt::ItemFlags BenchmarkModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractItemModel::flags(index);
}

bool BenchmarkModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid())
	{
		auto row = index.row();
		if (role == Qt::EditRole)
		{
			BmColumns::Columns cols = m_bmColumns->indexToColumns(index.column());
			if (cols == BmColumns::Columns::STATUS &&
				m_benchmarks[row].isSelected != value.toBool())
			{
				m_benchmarks[row].isSelected = value.toBool();
				emit dataChanged(createIndex(index.row(), 0), createIndex(index.row(), m_bmColumns->getColumnCount() - 1));

				if (m_benchmarks[row].isSelected)
				{
					emit measurementActive(m_benchmarks[row].measurement);
				}
				else
				{
					emit measurementInactive(m_benchmarks[row].measurement);
				}

				return true;
			}
		}
		else if (role == Qt::BackgroundColorRole)
		{
			m_benchmarks[row].hexColor = value.toString();
			return true;
		}
	}

	return false;
}
