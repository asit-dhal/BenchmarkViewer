#include "benchmark.h"

QString Benchmark::getName() const
{
    return name;
}

void Benchmark::setName(const QString &value)
{
    name = value;
}

quint64 Benchmark::getIterations() const
{
    return iterations;
}

void Benchmark::setIterations(quint64 value)
{
    iterations = value;
}

quint64 Benchmark::getRealTime() const
{
    return realTime;
}

void Benchmark::setRealTime(quint64 value)
{
    realTime = value;
}

quint64 Benchmark::getCpuTime() const
{
    return cpuTime;
}

void Benchmark::setCpuTime(quint64 value)
{
    cpuTime = value;
}

QString Benchmark::getTimeUnit() const
{
    return timeUnit;
}

void Benchmark::setTimeUnit(const QString &value)
{
    timeUnit = value;
}

QDebug operator<< (QDebug d, const Benchmark &bmk)
{
    d << "name: " << bmk.getName()
      << " iterations: " << bmk.getIterations()
      << " real_time: " << bmk.getRealTime()
      << " cpu_time: " << bmk.getCpuTime()
      << " time_unit: " << bmk.getTimeUnit();
    return d;
}
