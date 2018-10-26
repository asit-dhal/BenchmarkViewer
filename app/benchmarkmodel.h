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

#ifndef BENCHMARKMODEL_H
#define BENCHMARKMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QLoggingCategory>
#include "benchmark.h"
#include "measurement.h"

Q_DECLARE_LOGGING_CATEGORY(benchmarkModel);

struct BenchmarkViewUnit 
{
	Measurement measurement;
	QString filename;
	bool isSelected{false};
};

class BmColumns;

class BenchmarkModel : public QAbstractTableModel 
{
	Q_OBJECT
 public:
	explicit BenchmarkModel(BmColumns* bmColumns, QObject* parent = nullptr);
	void addBenchmark(QString filename, Benchmark benchmarks);
	void removeBenchmark(QString filename);
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

 signals:
	void measurementActive(Measurement);
	void measurementInactive(Measurement);

 private:
	QList<BenchmarkViewUnit> m_benchmarks;
	BmColumns* m_bmColumns;
};

#endif  // BENCHMARKMODEL_H
