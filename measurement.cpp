#include "measurement.h"
#include "helper.h"

Measurement::Measurement() noexcept {
  m_id = Helper::getUniqueMeasurementId();
}

QString Measurement::getName() const {
  return m_name;
}

void Measurement::setName(const QString& value) {
  m_name = value;
}

quint64 Measurement::getIterations() const {
  return m_iterations;
}

void Measurement::setIterations(quint64 value) {
  m_iterations = value;
}

quint64 Measurement::getRealTime() const {
  return m_realTime;
}

void Measurement::setRealTime(quint64 value) {
  m_realTime = value;
}

quint64 Measurement::getCpuTime() const {
  return m_cpuTime;
}

void Measurement::setCpuTime(quint64 value) {
  m_cpuTime = value;
}

QString Measurement::getTimeUnit() const {
  return m_timeUnit;
}

void Measurement::setTimeUnit(const QString& value) {
  m_timeUnit = value;
}

int Measurement::getId() const {
  return m_id;
}

QDebug operator<<(QDebug d, const Measurement& mmt) {
  d << "id: " << mmt.getId() << "name: " << mmt.getName()
    << " iterations: " << mmt.getIterations()
    << " real_time: " << mmt.getRealTime() << " cpu_time: " << mmt.getCpuTime()
    << " time_unit: " << mmt.getTimeUnit();
  return d;
}
