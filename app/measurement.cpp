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
