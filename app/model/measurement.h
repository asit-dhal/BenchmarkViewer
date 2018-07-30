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

#ifndef ITEM_H
#define ITEM_H

#include <QDebug>
#include <QString>

namespace model {

class Measurement {
 public:
  Measurement() noexcept;
  QString getName() const;
  void setName(const QString& value);

  quint64 getIterations() const;
  void setIterations(quint64 value);

  quint64 getRealTime() const;
  void setRealTime(quint64 value);

  quint64 getCpuTime() const;
  void setCpuTime(quint64 value);

  QString getTimeUnit() const;
  void setTimeUnit(const QString& value);

  int getId() const;

  quint64 getBytesPerSecond() const;
  void setBytesPerSecond(const quint64& bytesPerSecond);

  quint64 getItemsPerSecond() const;
  void setItemsPerSecond(const quint64& itemsPerSecond);

  QString getLabel() const;
  void setLabel(const QString& label);

  bool getErrorOccured() const;
  void setErrorOccured(bool errorOccured);

  QString getErrorMessage() const;
  void setErrorMessage(const QString& errorMessage);

  QString getFileName() const;
  void setFileName(const QString& fileName);

  enum class Attributes : int {
    eName = 0,
    eFileName,
    eIterations,
    eRealTime,
    eCpuTime,
    eTimeUnit,
    eBytesPerSecond,
    eItemsPerSecond,
    eLabel,
    eErrorOccured,
    eErrorMessage,
    eIsSelected,
    eId,
  };

  static QMap<Attributes, QString> getAttributeNames();

  bool isSelected() const;
  void setSelected(bool isSelected);

 private:
  QString m_name;
  QString m_fileName;
  quint64 m_iterations;
  quint64 m_realTime;
  quint64 m_cpuTime;
  QString m_timeUnit;
  quint64 m_bytesPerSecond;
  quint64 m_itemsPerSecond;
  QString m_label;
  bool m_errorOccured;
  QString m_errorMessage;
  bool m_isSelected{false};
  int m_id;
};

using Measurements = QVector<Measurement>;

QDebug operator<<(QDebug d, const Measurement& mmt);

}  // namespace model

Q_DECLARE_METATYPE(model::Measurement::Attributes);
Q_DECLARE_METATYPE(model::Measurement);

#endif  // ITEM_H
