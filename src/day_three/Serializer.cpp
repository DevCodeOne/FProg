#include <cassert>

#include <iostream>

#include "Serializer.h"

namespace FProg {

  void StringSerializer::start(const std::string &start) {
    assert(!m_is_started);

    m_value += "{";
    m_value += std::string(" ") + start;
    m_is_started = true;
  }

  void StringSerializer::write(const AttributeValue &attribvalue) {
    assert(m_is_started);

    if (attribvalue)
      m_value += " " + static_cast<std::string>(attribvalue);
  }

  void StringSerializer::end() {
    assert(m_is_started);

    m_value += " }\n";
    m_is_started = false;
  }

  const std::string StringSerializer::value() const {
    return m_value;
  }

}
