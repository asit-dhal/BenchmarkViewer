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

#include "model/jsonparser.h"
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "model/model_globals.h"

namespace model {

JsonParser::JsonParser(QObject* parent) : IAbstractParser(parent) {
  qCDebug(MODEL_TAG) << "Parser created";
}

void JsonParser::parse(QString filename) {
  qCDebug(MODEL_TAG) << "Parsing started: " << filename;
  QFile file;
  file.setFileName(filename);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString fileContent = file.readAll();
  file.close();

  Measurements mmts;

  QJsonDocument jsonDocument = QJsonDocument::fromJson(fileContent.toUtf8());
  QJsonObject jsonObj = jsonDocument.object();
  // benchmark.setContext(parseContext(jsonObj));
  mmts = parseBenchmarks(jsonObj, QFileInfo(filename).fileName());
  emit parsingFinished(filename, mmts);
  qCDebug(MODEL_TAG) << "Parsing finished: " << filename;
}

QVector<Measurement> JsonParser::parseBenchmarks(const QJsonObject& json,
                                                 QString filename) {
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

      mmt.setFileName(filename);

      mmts.push_back(mmt);
    }
  } else {
    qCCritical(MODEL_TAG) << "No benchmark exists";
  }

  qCDebug(MODEL_TAG) << "No. of measurements: " << mmts.size();

  return mmts;
}

}  // namespace model
