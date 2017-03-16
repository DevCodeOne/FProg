#pragma once

#include <string>

namespace FProg {

  class Serializer;
  class Deserializer;

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

}

inline std::ostream &operator<<(std::ostream &os,
                               const FProg::AttributeValue &value) {
  return os << static_cast<std::string>(value);
}

inline std::istream &operator>>(std::istream &is,
                                FProg::AttributeValue &value) {
  std::string in;

  is >> in;
  value.name(in);

  is >> in;

  if (in != "=") {
    value.name("");

    return is;
  }

  is >> in;
  value.value(in);

  return is;
}
