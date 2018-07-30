#ifndef PARSER_FACTORY_H
#define PARSER_FACTORY_H

#include <QObject>
#include <QSharedPointer>
#include "abstractparser.h"

namespace model {

class ParserFactory : QObject {
 public:
  enum class ParserType {
    eCsvParser,
    eJsonParser,
  };
  static QSharedPointer<IAbstractParser> getParser(ParserType type);

 private:
  ParserFactory() = default;
  ParserFactory(ParserFactory const&);
  void operator=(ParserFactory const&);
};
}  // namespace model

#endif
