#pragma once

#include <string>
#include <sstream>

#include "Attribute.h"

namespace FProg {

  class Deserealizer {
  public:
    Deserealizer() = default;
    virtual ~Deserealizer() = default;
    virtual bool begin(const std::string &token) = 0;
    virtual AttributeValue read() = 0;
    virtual bool end() = 0;
  };

  class StringDeserealizer final : public Deserealizer {
  public:
    StringDeserealizer(const std::string &input);
    virtual ~StringDeserealizer() = default;
    virtual bool begin(const std::string &token) override;
    virtual AttributeValue read() override;
    virtual bool end() override;
  private:
    std::istringstream m_input;
  };
}
