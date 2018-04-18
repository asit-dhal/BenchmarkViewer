#ifndef PARSER_H
#define PARSER_H

#include <QJsonObject>
#include <QObject>
#include <QVector>
#include "benchmarks.h"

class Parser : public QObject {
  Q_OBJECT
 public:
  Parser(QObject* parent = nullptr);
  void parse(QString filename);
 signals:
  void parsingStatus(QString statusMsg);
  void parsingFinished(QString fileName, Benchmarks Benchmark);

 private:
  Context parseContext(const QJsonObject& json);
  QVector<Benchmark> parseBenchmarks(const QJsonObject& json);
};

#endif  // PARSER_H
