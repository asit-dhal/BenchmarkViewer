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

#include "jsonparser.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "globals.h"

JsonParser::JsonParser(QObject* parent) : AbstractParser(parent) {}

void JsonParser::parse(QString filename) {
  emit parsingStatus(QString("Parsing started: ") + filename);
  qCDebug(parser) << "Parsing started: " << filename;
  QFile file;
  file.setFileName(filename);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString fileContent = file.readAll();
  file.close();

  Benchmark benchmark;

  QJsonDocument jsonDocument = QJsonDocument::fromJson(fileContent.toUtf8());
  QJsonObject jsonObj = jsonDocument.object();
  benchmark.setContext(parseContext(jsonObj));
  benchmark.setMeasurements(parseBenchmarks(jsonObj));
  emit parsingFinished(filename, benchmark);
  emit parsingStatus(QString("Parsing finished: ") + filename);
  qCDebug(parser) << "Parsing finished: " << filename;
}

Context JsonParser::parseContext(const QJsonObject& json) {
  Context ctx;
  if (json.contains("context")) {
    QJsonObject ctxJObject = json["context"].toObject();
    if (ctxJObject.contains("date") && ctxJObject["date"].isString()) {
      auto timestampStr = ctxJObject["date"].toString();
      QDateTime timestamp = QDateTime::fromString(
          timestampStr, "yyyy-MM-dd HH:mm:ss");  // 2017-12-09 22:01:41
      ctx.setTimestamp(timestamp);
    }
    if (ctxJObject.contains("num_cpus") && ctxJObject["num_cpus"].isDouble()) {
      ctx.setCpuCount(ctxJObject["num_cpus"].toInt());
    }
    if (ctxJObject.contains("mhz_per_cpu") &&
        ctxJObject["mhz_per_cpu"].isDouble()) {
      ctx.setCpuFrequency(ctxJObject["mhz_per_cpu"].toInt());
    }
    if (ctxJObject.contains("cpu_scaling_enabled") &&
        ctxJObject["cpu_scaling_enabled"].isBool()) {
      ctx.setCpuScalingEnabled(ctxJObject["cpu_scaling_enabled"].toBool());
    }
    if (ctxJObject.contains("library_build_type") &&
        ctxJObject["library_build_type"].isString()) {
      ctx.setLibraryBuildType(ctxJObject["library_build_type"].toString());
    }
  } else {
    qCCritical(parser) << "No context exists";
  }
  qCDebug(parser) << "Context: " << ctx;
  return ctx;
}

QVector<Measurement> JsonParser::parseBenchmarks(const QJsonObject& json) {
  QVector<Measurement> mmts;
  if (json.contains("benchmarks") && json["benchmarks"].isArray()) {
    QJsonArray jsonArrayObject = json["benchmarks"].toArray();
    foreach (const QJsonValue& value, jsonArrayObject) {
      QJsonObject jsonObj = value.toObject();
      Measurement mmt;

      if (jsonObj.contains("name") && jsonObj["name"].isString()) {
        mmt.setName(jsonObj["name"].toString());
      }

      if (jsonObj.contains("iterations") && jsonObj["iterations"].isDouble()) {
        mmt.setIterations(jsonObj["iterations"].toVariant().toLongLong());
      }

      if (jsonObj.contains("real_time") && jsonObj["real_time"].isDouble()) {
        mmt.setRealTime(jsonObj["real_time"].toVariant().toLongLong());
      }

      if (jsonObj.contains("cpu_time") && jsonObj["cpu_time"].isDouble()) {
        mmt.setCpuTime(jsonObj["cpu_time"].toVariant().toLongLong());
      }

      if (jsonObj.contains("time_unit") && jsonObj["time_unit"].isString()) {
        mmt.setTimeUnit(jsonObj["time_unit"].toString());
      }

      mmts.push_back(mmt);
    }
  } else {
    qCCritical(parser) << "No benchmark exists";
  }

  qCDebug(parser) << "No. of measurements: " << mmts.size();

  return mmts;
}
