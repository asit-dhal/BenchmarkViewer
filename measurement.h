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
