#include "parser.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

Parser::Parser(QObject* parent) {}

void Parser::parse(QString filename) {
  emit parsingStatus(QString("Parsing started: ") + filename);
  qDebug() << "Parsing started: " << filename;
  QFile file;
  file.setFileName(filename);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString fileContent = file.readAll();
  file.close();

  Benchmarks benchmarks;

  QJsonDocument jsonDocument = QJsonDocument::fromJson(fileContent.toUtf8());
  QJsonObject jsonObj = jsonDocument.object();
  benchmarks.setContext(parseContext(jsonObj));
  benchmarks.setBenchmarks(parseBenchmarks(jsonObj));
  emit parsingFinished(filename, benchmarks);
  emit parsingStatus(QString("Parsing finished: ") + filename);
}

Context Parser::parseContext(const QJsonObject& json) {
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
    qDebug() << "No context exists";
  }
  return ctx;
}

QVector<Benchmark> Parser::parseBenchmarks(const QJsonObject& json) {
  QVector<Benchmark> benchmarks;
  if (json.contains("benchmarks") && json["benchmarks"].isArray()) {
    QJsonArray jsonArrayObject = json["benchmarks"].toArray();
    foreach (const QJsonValue& value, jsonArrayObject) {
      QJsonObject jsonObj = value.toObject();
      Benchmark benchmark;

      if (jsonObj.contains("name") && jsonObj["name"].isString()) {
        benchmark.setName(jsonObj["name"].toString());
      }

      if (jsonObj.contains("iterations") && jsonObj["iterations"].isDouble()) {
        benchmark.setIterations(jsonObj["iterations"].toVariant().toLongLong());
      }

      if (jsonObj.contains("real_time") && jsonObj["real_time"].isDouble()) {
        benchmark.setRealTime(jsonObj["real_time"].toVariant().toLongLong());
      }

      if (jsonObj.contains("cpu_time") && jsonObj["cpu_time"].isDouble()) {
        benchmark.setCpuTime(jsonObj["cpu_time"].toVariant().toLongLong());
      }

      if (jsonObj.contains("time_unit") && jsonObj["time_unit"].isString()) {
        benchmark.setTimeUnit(jsonObj["time_unit"].toString());
      }

      benchmarks.push_back(benchmark);
    }
  } else {
    qDebug() << "No benchmark exists";
  }

  return benchmarks;
}
