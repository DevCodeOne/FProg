#pragma once

#include <string>

#include "Attribute.h"
#include "Deserializer.h"

namespace FProg {

  class Serializer {
  public:
    Serializer() = default;
    virtual ~Serializer() = default;
    virtual void start(const std::string &start) = 0;
    virtual void write(const AttributeValue &attribvalue) = 0;
    virtual void end() = 0;
  };

  class StringSerializer final : public Serializer {
  public:
    StringSerializer() = default;
    virtual ~StringSerializer() = default;
    virtual void start(const std::string &start) override;
    virtual void write(const AttributeValue &attribvalue) override;
    virtual void end() override;
    const std::string value() const;
  private:
    bool m_is_started = false;
    std::string m_value;
  };

}
