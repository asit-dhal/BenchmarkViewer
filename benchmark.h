#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QDebug>

class Benchmark
{
public:
    Benchmark() = default;
    QString getName() const;
    void setName(const QString &value);

    quint64 getIterations() const;
    void setIterations(quint64 value);

    quint64 getRealTime() const;
    void setRealTime(quint64 value);

    quint64 getCpuTime() const;
    void setCpuTime(quint64 value);

    QString getTimeUnit() const;
    void setTimeUnit(const QString &value);

private:
    QString name;
    quint64 iterations;
    quint64 realTime;
    quint64 cpuTime;
    QString timeUnit;
};

QDebug operator<< (QDebug d, const Benchmark &bmk);

#endif // ITEM_H
