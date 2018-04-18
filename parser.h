#ifndef PARSER_H
#define PARSER_H

#include <QJsonObject>
#include <QObject>
#include <QVector>
#include "benchmark.h"

class Parser : public QObject {
  Q_OBJECT
 public:
  Parser(QObject* parent = nullptr);
  void parse(QString filename);
 signals:
  void parsingStatus(QString statusMsg);
  void parsingFinished(QString fileName, Benchmark benchmark);

 private:
  Context parseContext(const QJsonObject& json);
  QVector<Measurement> parseBenchmarks(const QJsonObject& json);
};

#endif  // PARSER_H
