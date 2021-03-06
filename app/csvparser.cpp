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

#include "csvparser.h"
#include <QFile>
#include <QRegExp>
#include <QVector>
#include "globals.h"

void CsvParser::parse(QString filename)
{
	qCDebug(parser) << "Parsing started: " << filename;
	QFile file;
	file.setFileName(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QString fileContent = file.readAll();
	file.close();

    QStringList lines = fileContent.split(QRegExp("[\r\n]"),
                                          QString::SkipEmptyParts);

	QStringList headerFields = parseHeaders(lines.at(0));
	lines.pop_front();
	auto mmts = parseBenchmarks(lines, headerFields);
	m_benchmark.setMeasurements(mmts.toVector());
	qCDebug(parser) << "Parsing finished: " << filename;
}

QStringList CsvParser::parseHeaders(QString header)
{
	QStringList fields = header.split(",", QString::KeepEmptyParts);
	QList<QString> headerFields;
	for (QString s : fields) 
	{
		headerFields.append(s.trimmed());
	}
	return headerFields;
}

QList<Measurement> CsvParser::parseBenchmarks(QStringList& data,
                                              QStringList& header)
{
	QList<Measurement> mmts;
	for (auto const& rec : data)
	{
		QStringList fields = rec.split(",", QString::KeepEmptyParts);

		Measurement mmt;
		for (auto i = 0; i < header.size(); i++)
		{
			qCDebug(parser) << "Data: " << fields;
			if (header.at(i).compare("name", Qt::CaseInsensitive) == 0)
			{
				QString name = fields.at(i);
				name.replace("'", "");
				name.replace("\"", "");
				mmt.setName(name);
			}
            else if (header.at(i).compare("iterations",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setIterations(fields.at(i).toDouble());
			}
            else if (header.at(i).compare("real_time",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setRealTime(fields.at(i).toDouble());
			}
            else if (header.at(i).compare("cpu_time",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setCpuTime(fields.at(i).toDouble());
			}
            else if (header.at(i).compare("time_unit",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setTimeUnit(fields.at(i));
			} 
            else if (header.at(i).compare("bytes_per_second",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setBytesPerSecond(fields.at(i).toDouble());
			} 
            else if (header.at(i).compare("items_per_second",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setItemsPerSecond(fields.at(i).toDouble());
			}
            else if (header.at(i).compare("label",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setLabel(fields.at(i).trimmed());
			}
            else if (header.at(i).compare("error_occured",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setErrorOccured(fields.at(i).toInt());
			}
            else if (header.at(i).compare("error_message",
                                          Qt::CaseInsensitive) == 0)
			{
				mmt.setErrorMessage(fields.at(i).trimmed());
			}
			else
			{
                qCDebug(parser) << "Error occured Unknown field: "
                                << fields.at(i);
			}
		}
		mmts.append(mmt);
	}
  return mmts;
}

Benchmark CsvParser::getBenchmark() const
{
	return m_benchmark;
}
