/*=========================================================================

   Program: QCommander

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
#include "abstractparser.h"

#include "csvparser.h"
#include "jsonparser.h"

std::unique_ptr<IAbstractParser> ParserFactory::getParser(
    ParserType parserType)
{
	switch (parserType)
	{
	case ParserType::eGoogleBenchmarkCsv:
		return std::make_unique<CsvParser>();
	case ParserType::eGoogleBenchmarkJson:
		return std::make_unique<JsonParser>();
	}
}

QDebug operator<<(QDebug d, const ParserType& type)
{
	switch (type)
	{
    case ParserType::eGoogleBenchmarkCsv:
        d << "GoogleBenchmarkCsv";
        break;
    case ParserType::eGoogleBenchmarkJson:
        d << "GoogleBenchmarkJson";
        break;
	}
	return d;
}
