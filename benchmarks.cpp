#include "benchmarks.h"

Benchmarks::Benchmarks()
{

}

Context Benchmarks::getContext() const
{
    return context;
}

void Benchmarks::setContext(const Context &value)
{
    context = value;
}

QVector<Benchmark> Benchmarks::getBenchmarks() const
{
    return benchmarks;
}

void Benchmarks::addBenchmark(const Benchmark& _benchmark)
{
    benchmarks.append(_benchmark);
}

void Benchmarks::setBenchmarks(const QVector<Benchmark> &value)
{
    benchmarks = value;
}

QDebug operator<< (QDebug d, const Benchmarks &bmks)
{
    d << "context: {" << bmks.getContext() << "}"
      << " benchmarks: [" << bmks.getBenchmarks() << "]";
    return d;
}
