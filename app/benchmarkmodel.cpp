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

Q_LOGGING_CATEGORY(benchmarkModel, "benchmarkModel")

BenchmarkModel *BenchmarkModel::m_pInstance = nullptr;

BenchmarkModel *BenchmarkModel::getInstance()
{
    return m_pInstance;
}


BenchmarkModel::BenchmarkModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    m_pInstance = this;
	initializeMetaData();
}

const int BenchmarkModel::COLUMN_COUNT = 7;

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

		if (static_cast<Columns>(section) != Columns::eInvalid) 
		{
			return toString(static_cast<Columns>(section));
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
	return COLUMN_COUNT;
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
		Columns col = static_cast<Columns>(index.column());
		switch (col)
		{
		case Columns::eStatus:
			return viewunit.isSelected;
		case Columns::eName:
			return viewunit.measurement.getName();
		case Columns::eIterations:
			return viewunit.measurement.getIterations();
		case Columns::eRealTime:
			return viewunit.measurement.getRealTime();
		case Columns::eCpuTime:
			return viewunit.measurement.getCpuTime();
		case Columns::eTimeUnit:
			return viewunit.measurement.getTimeUnit();
		case Columns::eFilename:
			return QFileInfo(viewunit.filename).fileName();
		default:
			return QVariant();
		}
	}

	if (role == Qt::ToolTipRole)
	{
		BenchmarkViewUnit viewunit = m_benchmarks.at(index.row());
		Columns col = static_cast<Columns>(index.column());
		switch (col)
		{
		case Columns::eFilename:
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
			Columns col = static_cast<Columns>(index.column());
			if (col == Columns::eStatus && m_benchmarks[row].isSelected != value.toBool())
			{
				m_benchmarks[row].isSelected = value.toBool();
				emit dataChanged(createIndex(index.row(), 0), createIndex(index.row(), COLUMN_COUNT - 1));

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

void BenchmarkModel::initializeMetaData()
{

	m_columnsVisibility[Columns::eStatus] = true;
	m_columnsVisibility[Columns::eName] = true;
	m_columnsVisibility[Columns::eIterations] = true;
	m_columnsVisibility[Columns::eRealTime] = true;
	m_columnsVisibility[Columns::eCpuTime] = true;
	m_columnsVisibility[Columns::eTimeUnit] = true;
	m_columnsVisibility[Columns::eFilename] = true;
}

bool BenchmarkModel::getColumnVisibility(Columns col)
{
	return m_columnsVisibility[col];
}


void BenchmarkModel::setColumnVisibility(Columns col, bool visibility)
{
	m_columnsVisibility[col] = visibility;
	emit columnVisibilityChanged(col, visibility);
}

QString toString(BenchmarkModel::Columns col)
{
	using Columns = BenchmarkModel::Columns;
	switch (col)
	{
	case Columns::eStatus: return QObject::tr("Status");
	case Columns::eName: return QObject::tr("Name");
	case Columns::eIterations: return QObject::tr("Iterations");
	case Columns::eRealTime: return QObject::tr("Realtime");
	case Columns::eCpuTime: return QObject::tr("Cpu Time");
	case Columns::eTimeUnit: return QObject::tr("Timeunit");
	case Columns::eFilename: return QObject::tr("Filename");
	default: return QObject::tr("Unknown");
	}
}

