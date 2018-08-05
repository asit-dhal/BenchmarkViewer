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

#include "model/measurement.h"
#include "model/helper.h"

namespace model {

Measurement::Measurement() noexcept {
  m_id = Helper::getUniqueMeasurementId();
  m_name = "";
  m_iterations = 0;
  m_realTime = 0;
  m_cpuTime = 0;
  m_timeUnit = "";
  m_bytesPerSecond = 0;
  m_itemsPerSecond = 0;
  m_label = "";
  m_errorOccured = false;
  m_errorMessage = "";
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

quint64 Measurement::getBytesPerSecond() const {
  return m_bytesPerSecond;
}

void Measurement::setBytesPerSecond(const quint64& bytesPerSecond) {
  m_bytesPerSecond = bytesPerSecond;
}

quint64 Measurement::getItemsPerSecond() const {
  return m_itemsPerSecond;
}

void Measurement::setItemsPerSecond(const quint64& itemsPerSecond) {
  m_itemsPerSecond = itemsPerSecond;
}

QString Measurement::getLabel() const {
  return m_label;
}

void Measurement::setLabel(const QString& label) {
  m_label = label;
}

bool Measurement::getErrorOccured() const {
  return m_errorOccured;
}

void Measurement::setErrorOccured(bool errorOccured) {
  m_errorOccured = errorOccured;
}

QString Measurement::getErrorMessage() const {
  return m_errorMessage;
}

void Measurement::setErrorMessage(const QString& errorMessage) {
  m_errorMessage = errorMessage;
}

QString Measurement::getFileName() const {
  return m_fileName;
}

void Measurement::setFileName(const QString& fileName) {
  m_fileName = fileName;
}

QMap<Measurement::Attributes, QString> Measurement::getAttributeNames() {
  auto initializeMap = []() {
    QMap<Attributes, QString> map;
    map.insert(Attributes::eName, "Name");
    map.insert(Attributes::eFileName, "FileName");
    map.insert(Attributes::eIterations, "Iterations");
    map.insert(Attributes::eRealTime, "RealTime");
    map.insert(Attributes::eCpuTime, "CpuTime");
    map.insert(Attributes::eTimeUnit, "TimeUnit");
    map.insert(Attributes::eBytesPerSecond, "BytesPerSecond");
    map.insert(Attributes::eItemsPerSecond, "ItemsPerSecond");
    map.insert(Attributes::eLabel, "Label");
    map.insert(Attributes::eErrorOccured, "ErrorOccured");
    map.insert(Attributes::eErrorMessage, "ErrorMessage");
    map.insert(Attributes::eIsSelected, "Selected");
    map.insert(Attributes::eId, "Id");
    return map;
  };
  static QMap<Attributes, QString> metaData = initializeMap();
  return metaData;
}

bool Measurement::isSelected() const {
  return m_isSelected;
}

void Measurement::setSelected(bool isSelected) {
  m_isSelected = isSelected;
}

QDebug operator<<(QDebug d, const Measurement& mmt) {
  d << "id: " << mmt.getId() << "name: " << mmt.getName()
    << " iterations: " << mmt.getIterations()
    << " real_time: " << mmt.getRealTime() << " cpu_time: " << mmt.getCpuTime()
    << " time_unit: " << mmt.getTimeUnit();
  d << " bytes_per_second: " << mmt.getBytesPerSecond()
    << " items_per_second: " << mmt.getItemsPerSecond()
    << " label: " << mmt.getLabel()
    << " error_occured: " << mmt.getErrorOccured()
    << " error_message: " << mmt.getErrorMessage();
  return d;
}

}  // namespace model
