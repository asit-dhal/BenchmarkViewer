#include "model/parserfactory.h"
#include "model/csvparser.h"
#include "model/jsonparser.h"

namespace model {
QSharedPointer<IAbstractParser> ParserFactory::getParser(ParserType type) {
  static QSharedPointer<IAbstractParser> jsonParser(new JsonParser);
  static QSharedPointer<IAbstractParser> csvParser(new CsvParser);
  switch (type) {
    case ParserType::eCsvParser:
      return csvParser;
    case ParserType::eJsonParser:
      return jsonParser;
  }
}
}  // namespace model
