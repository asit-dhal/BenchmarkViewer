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

 private:
  QString m_name;
  quint64 m_iterations;
  quint64 m_realTime;
  quint64 m_cpuTime;
  QString m_timeUnit;
  int m_id;
};

Q_DECLARE_METATYPE(Measurement);

QDebug operator<<(QDebug d, const Measurement& mmt);

#endif  // ITEM_H
