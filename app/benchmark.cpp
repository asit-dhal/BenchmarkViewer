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

#include "benchmark.h"

Benchmark::Benchmark() {}

Context Benchmark::getContext() const 
{
	return m_context;
}

void Benchmark::setContext(const Context& value) 
{
	m_context = value;
}

QVector<Measurement> Benchmark::getMeasurements() const 
{
  return m_measurements;
}

void Benchmark::addMeasurement(const Measurement& _mmt) 
{
	m_measurements.append(_mmt);
}

void Benchmark::setMeasurements(const QVector<Measurement>& value) 
{
	m_measurements = value;
}

QDebug operator<<(QDebug d, const Benchmark& bmk) 
{
	d << "context: {" << bmk.getContext() << "}"
		<< " benchmarks: [" << bmk.getMeasurements() << "]";
  return d;
}
