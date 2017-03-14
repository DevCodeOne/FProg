#pragma once

#include <string>

namespace FProg {

  // Eigene Klasse um das Vertauschen von Parametern zu verhindern
  class AttributeValue {
  public:
    inline AttributeValue &value(const std::string &value) {
      m_value = value;
      return *this;
    }

    inline AttributeValue &name(const std::string &name) {
      m_name = name;
      return *this;
    }

    inline const std::string& value() const {
      return m_value;
    }

    inline const std::string &name() const {
      return m_name;
    }

    // Safe-bool idiom : Verhindert ungewollte
    // Konvertierung zu bool
    inline explicit operator bool() const {
      return m_name.size() != 0;
    }

    inline operator std::string() const {
      return m_name + " = " + m_value;
    }

  private:
    std::string m_name;
    std::string m_value;
  };

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
    virtual void start(const std::string &start) override;
    virtual void write(const AttributeValue &attribvalue) override;
    virtual void end() override;
    virtual ~StringSerializer() = default;

    const std::string value() const;
  private:
    bool m_is_started = false;
    std::string m_value;
  };

  inline std::ostream &operator<<(std::ostream &os,
                                  const StringSerializer &serializer) {
    return os << serializer.value();
  }
}
