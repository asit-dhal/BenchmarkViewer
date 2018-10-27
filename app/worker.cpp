#include "worker.h"
#include "globals.h"

void Worker::parse(ParserType parserType, QString filename)
{
	qCDebug(parser) << "Request Arrived to parse: " << filename << " type: " << parserType;
	auto parser = ParserFactory::getParser(parserType);
	parser->parse(filename);
	auto benchmark = parser->getBenchmark();
	emit parsingFinished(filename, benchmark);
	//qCDebug(parser) << "Parsing finished: " << filename << " type: " << parserType;
}