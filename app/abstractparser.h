/*=========================================================================

   Program: BenchmarkViewer

   Copyright (c) 2018 Asit Dhal
   All rights reserved.

   QCommander is a free software; you can redistribute it and/or modify it.


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

#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QString>
#include <memory>
#include <QList>
#include "benchmark.h"

class IAbstractParser
{
 public:
	virtual ~IAbstractParser() = default;
	virtual void parse(QString filename) = 0;
	virtual Benchmark getBenchmark() const = 0;
};


enum class ParserType
{
	eUnknown,
	eGoogleBenchmarkCsv,
	eGoogleBenchmarkJson,
};

class ParserFactory
{
public:
	static std::unique_ptr<IAbstractParser> getParser(ParserType parserType);
};

Q_DECLARE_METATYPE(ParserType);

QDebug operator<<(QDebug d, const ParserType& type);



#endif  // ABSTRACTPARSER_H
