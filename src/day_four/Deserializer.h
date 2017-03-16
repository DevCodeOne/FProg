#pragma once

#include <string>
#include <sstream>

#include "Attribute.h"

namespace FProg {

  class Deserializer {
  public:
    Deserializer() = default;
    virtual ~Deserializer() = default;
    virtual bool start(const std::string &token) = 0;
    virtual AttributeValue read() = 0;
    virtual bool end() = 0;
  };

  class StringDeserializer final : public Deserializer {
  public:
    StringDeserializer(const std::string &input);
    virtual ~StringDeserializer() = default;
    virtual bool start(const std::string &token) override;
    virtual AttributeValue read() override;
    virtual bool end() override;
  private:
    std::istringstream m_input;
  };
}
