#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <QVector>
#include "context.h"
#include "measurement.h"

class Benchmark {
 public:
  Benchmark();

  Context getContext() const;
  void setContext(const Context& value);

  QVector<Measurement> getMeasurements() const;
  void addMeasurement(const Measurement& _mmt);
  void setMeasurements(const QVector<Measurement>& value);

 private:
  Context m_context;
  QVector<Measurement> m_measurements;
};

QDebug operator<<(QDebug d, const Benchmark& bmk);

#endif  // BENCHMARKS_H
