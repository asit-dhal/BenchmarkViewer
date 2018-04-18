#include "benchmark.h"

Benchmark::Benchmark() {}

Context Benchmark::getContext() const {
  return m_context;
}

void Benchmark::setContext(const Context& value) {
  m_context = value;
}

QVector<Measurement> Benchmark::getMeasurements() const {
  return m_measurements;
}

void Benchmark::addMeasurement(const Measurement& _mmt) {
  m_measurements.append(_mmt);
}

void Benchmark::setMeasurements(const QVector<Measurement>& value) {
  m_measurements = value;
}

QDebug operator<<(QDebug d, const Benchmark& bmk) {
  d << "context: {" << bmk.getContext() << "}"
    << " benchmarks: [" << bmk.getMeasurements() << "]";
  return d;
}
