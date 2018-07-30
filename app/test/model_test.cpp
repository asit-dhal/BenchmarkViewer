#include "model_test.h"
#include <QDebug>
#include <QTest>
#include "parserfactory.h"

ModelTester::ModelTester(QObject* parent) : QObject(parent) {}

void ModelTester::initTestCase() {
  m_csvParser = model::ParserFactory::getParser(
      model::ParserFactory::ParserType::eCsvParser);
  m_jsonParser = model::ParserFactory::getParser(
      model::ParserFactory::ParserType::eJsonParser);
}

void ModelTester::testCsvParser() {
  QString csvFilename =
      "/home/asit/qt_proj/BenchmarkViewer/test_data/creation.csv";
  QObject::connect(
      m_csvParser.data(), &model::IAbstractParser::parsingFinished,
      [this, csvFilename](QString filename, model::Measurements mmts) {
        QCOMPARE(csvFilename, filename);
        verifyMeasurements(mmts);
      });
  m_csvParser->parse(csvFilename);
}

void ModelTester::testJsonParser() {}

void ModelTester::cleanupTestCase() {}

void ModelTester::verifyMeasurements(model::Measurements mmts) {
  QCOMPARE(mmts.size(), 3);

  QCOMPARE(mmts.at(0).getName(), "String_Creation");
  QCOMPARE(mmts.at(0).getIterations(), 7218629);
  QCOMPARE(mmts.at(0).getRealTime(), 97.5736);
  QCOMPARE(mmts.at(0).getCpuTime(), 97.1294);
  QCOMPARE(mmts.at(0).getTimeUnit(), "ns");

  QCOMPARE(mmts.at(1).getName(), "StringStream_Creation");
  QCOMPARE(mmts.at(1).getIterations(), 868059);
  QCOMPARE(mmts.at(1).getRealTime(), 807.886);
  QCOMPARE(mmts.at(1).getCpuTime(), 806.38);
  QCOMPARE(mmts.at(1).getTimeUnit(), "ns");

  QCOMPARE(mmts.at(2).getName(), "OstringStream_Creation");
  QCOMPARE(mmts.at(2).getIterations(), 1131614);
  QCOMPARE(mmts.at(2).getRealTime(), 618.573);
  QCOMPARE(mmts.at(2).getCpuTime(), 618.503);
  QCOMPARE(mmts.at(2).getTimeUnit(), "ns");
}
