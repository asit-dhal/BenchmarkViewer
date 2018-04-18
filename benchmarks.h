#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include "context.h"
#include "benchmark.h"
#include <QVector>

class Benchmarks
{
public:
    Benchmarks();

    Context getContext() const;
    void setContext(const Context &value);

    QVector<Benchmark> getBenchmarks() const;
    void addBenchmark(const Benchmark& _benchmark);
    void setBenchmarks(const QVector<Benchmark> &value);

private:
    Context context;
    QVector<Benchmark> benchmarks;
};

QDebug operator<< (QDebug d, const Benchmarks &bmks);

#endif // BENCHMARKS_H
