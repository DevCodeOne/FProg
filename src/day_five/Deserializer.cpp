#include <iostream>

#include "Deserializer.h"
#include "Attribute.h"

namespace FProg {

  StringDeserializer::StringDeserializer(const std::string &input) :
    m_input(input) {
  }

  bool StringDeserializer::start(const std::string &token) {
    std::string in;
    m_input >> in;
    if (in != "{")
      return false;

    m_input >> in;

    if (in == token) {
      return true;
    } else {
      return false;
    }
  }

  AttributeValue StringDeserializer::read() {
    AttributeValue attribvalue;

    std::string in;
    m_input >> attribvalue;

    return attribvalue;
  }

  bool StringDeserializer::end() {
    std::string in;
    m_input >> in;

    return in == "}";
  }
}
